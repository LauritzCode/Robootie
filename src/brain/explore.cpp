#include "explore.h"
#include <Arduino.h>
#include "brain/behavior_fsm.h"
#include "actuators/drive.h"
#include "sensors/proximity_sensor.h"
#include "config/thresholds.h"
#include "core/timebase.h"

typedef enum {
    EXPLORE_IDLE = 0,
    EXPLORE_SCAN,
    EXPLORE_CHOOSE,
    EXPLORE_DRIVING,
    EXPLORE_BACKUP,
    EXPLORE_SILLY,
    EXPLORE_WONDER,
    EXPLORE_UTURN,
    EXPLORE_GREET,
    EXPLORE_TRAPPED,    // hit obstacles too many times — angry, waiting for rescue
} ExploreState;

static ExploreState   g_state             = EXPLORE_IDLE;
static uint32_t       g_state_enter_ms    = 0;
static SoundIntent    g_sound_intent      = {};

static uint16_t       g_scan_dist_L       = 9999;
static uint16_t       g_scan_dist_R       = 9999;
static uint16_t       g_scan_dist_C       = 9999;

static ProximityState g_last_prox         = PROXIMITY_FAR;
static uint32_t       g_next_silly_ms     = 0;
static uint32_t       g_explore_start_ms  = 0;

// per-state one-shot data set in enter(), consumed in update()
static uint32_t       g_state_duration_ms = 0;
static DriveDirection g_uturn_dir         = DRIVE_LEFT;
static bool           g_choose_decided    = false;
static uint32_t       g_backup_duration_ms = 1200;
static uint8_t        g_backup_exit       = 0;  // 0=scan,1=uturn,2=wonder,3=silly
static uint8_t        g_wonder_exit       = 0;  // 0=normal,1=greet,2=backup_silly

// stuck / trapped tracking
static uint8_t        g_stuck_count       = 0;
static uint32_t       g_drive_start_ms    = 0;
static uint16_t       g_trapped_dist_save = 9999;

static const uint32_t EXPLORE_TIMEOUT_MS   = 600000UL;  // 10 minutes
static const uint16_t EXPLORE_STOP_DIST    = 250;
static const uint16_t EXPLORE_BLOCKED_DIST = 280;
static const uint16_t EXPLORE_SCAN_RANGE   = 330;       // sensor read range — avoid below this
static const uint8_t  EXPLORE_STUCK_MAX    = 5;
static const uint32_t EXPLORE_STUCK_WINDOW = 5000;      // < 5s driving = stuck

// ── helpers ──────────────────────────────────────────────────────────────────

static void go(DriveDirection dir, uint8_t speed) {
    DriveIntent intent = {dir, speed};
    drive_set_intent(&intent);
}

static void queue_sound(SoundPatternID p) {
    g_sound_intent.play    = true;
    g_sound_intent.pattern = p;
}

static void enter(ExploreState next, uint32_t now_ms) {
    g_state          = next;
    g_state_enter_ms = now_ms;

    switch (next) {
        case EXPLORE_SCAN:
            g_scan_dist_L    = 9999;
            g_scan_dist_R    = 9999;
            g_scan_dist_C    = proximity_get_last_distance();
            g_choose_decided = false;
            go(DRIVE_STOP, 0);
            break;

        case EXPLORE_CHOOSE:
            g_choose_decided = false;
            go(DRIVE_STOP, 0);
            break;

        case EXPLORE_DRIVING:
            go(DRIVE_FORWARD, 100);
            g_drive_start_ms = now_ms;
            if (g_next_silly_ms == 0)
                g_next_silly_ms = now_ms + (uint32_t)random(10000, 20000);
            break;

        case EXPLORE_BACKUP:
            go(DRIVE_BACKWARD, 100);
            break;

        case EXPLORE_WONDER:
            go(DRIVE_STOP, 0);
            g_state_duration_ms = 1500 + (uint32_t)random(2000);  // 1.5–3.5s
            break;

        case EXPLORE_UTURN:
            g_uturn_dir = (random(2) == 0) ? DRIVE_LEFT : DRIVE_RIGHT;
            go(g_uturn_dir, 110);
            g_state_duration_ms = 1300 + (uint32_t)random(600);   // 1.3–1.9s
            queue_sound(SOUND_SPIN);
            break;

        case EXPLORE_SILLY:
            queue_sound(SOUND_SPIN);
            g_next_silly_ms = now_ms + (uint32_t)random(12000, 25000);
            break;

        case EXPLORE_GREET:
            go(DRIVE_STOP, 0);
            queue_sound(SOUND_DRIVE_HAPPY);  // happy chirp on arrival
            break;

        case EXPLORE_TRAPPED:
            g_trapped_dist_save = proximity_get_last_distance();
            go(DRIVE_STOP, 0);
            Serial.println("[EXPLORE] TRAPPED - too many obstacles");
            break;

        case EXPLORE_IDLE:
            go(DRIVE_STOP, 0);
            break;

        default:
            break;
    }
}

// Called when an obstacle is hit during DRIVING.
// Tracks stuck count and decides what to do.
static void handle_obstacle(uint32_t now_ms) {
    bool drove_short = (now_ms - g_drive_start_ms < EXPLORE_STUCK_WINDOW);

    if (drove_short) {
        g_stuck_count++;
        Serial.print("[EXPLORE] stuck_count="); Serial.println(g_stuck_count);
    } else {
        g_stuck_count = 0;
    }

    if (g_stuck_count >= EXPLORE_STUCK_MAX) {
        g_stuck_count = 0;
        enter(EXPLORE_TRAPPED, now_ms);
        return;
    }

    uint8_t roll = (uint8_t)random(100);

    if (roll < 30) {
        // 30% — back up
        g_backup_duration_ms = 1200;
        g_backup_exit        = (uint8_t)(random(3));  // 0=scan,1=uturn,2=wonder
        enter(EXPLORE_BACKUP, now_ms);

    } else if (roll < 80) {
        // 50% — stop and stare/think
        g_wonder_exit = (random(2) == 0) ? 1 : 2;  // 1=greet, 2=backup_silly
        enter(EXPLORE_WONDER, now_ms);

    } else {
        // 20% — rescan from here
        enter(EXPLORE_SCAN, now_ms);
    }
}

// ── public API ────────────────────────────────────────────────────────────────

void explore_init(void) {
    g_state       = EXPLORE_IDLE;
    g_stuck_count = 0;
}

void explore_start(uint32_t now_ms) {
    g_explore_start_ms = now_ms;
    g_last_prox        = proximity_get_state();
    g_next_silly_ms    = now_ms + (uint32_t)random(10000, 20000);
    g_stuck_count      = 0;
    g_drive_start_ms   = now_ms;
    behavior_fsm_set_state(BEHAVIOR_EXPLORE);
    enter(EXPLORE_SCAN, now_ms);
    Serial.println("[EXPLORE] start");
}

void explore_quit(void) {
    go(DRIVE_STOP, 0);
    g_state = EXPLORE_IDLE;
    behavior_fsm_set_state(BEHAVIOR_AWAKE);
    Serial.println("[EXPLORE] quit");
}

const SoundIntent* explore_get_sound_intent(void) { return &g_sound_intent; }

bool explore_is_silly(void)    { return g_state == EXPLORE_SILLY || g_state == EXPLORE_UTURN; }
bool explore_is_scanning(void) { return g_state == EXPLORE_SCAN  || g_state == EXPLORE_CHOOSE; }
bool explore_is_greeting(void) { return g_state == EXPLORE_GREET; }
bool explore_is_waving(void)   { return g_state == EXPLORE_GREET || g_state == EXPLORE_WONDER; }
bool explore_is_trapped(void)  { return g_state == EXPLORE_TRAPPED; }

// ── update ────────────────────────────────────────────────────────────────────

void explore_update(uint32_t now_ms) {
    g_sound_intent.play = false;

    if (g_state == EXPLORE_IDLE) return;
    if (behavior_fsm_get_state() != BEHAVIOR_EXPLORE) { g_state = EXPLORE_IDLE; return; }
    if (now_ms - g_explore_start_ms >= EXPLORE_TIMEOUT_MS) { explore_quit(); return; }

    uint32_t time_in_state = now_ms - g_state_enter_ms;
    uint16_t dist          = proximity_get_last_distance();
    ProximityState prox    = proximity_get_state();

    switch (g_state) {

        // ── SCAN: sweep left and right, capture three distances ───────────────
        case EXPLORE_SCAN: {
            //   0–300ms:    stopped, capture centre
            //   300–800ms:  spin left
            //   800–1100ms: stopped, capture left
            //   1100–2300ms: spin right (return through centre + overshoot right)
            //   2300–2600ms: stopped, capture right
            //   2600–3100ms: spin left (return to centre)
            //   3100ms+:    → CHOOSE
            if      (time_in_state < 300)  { go(DRIVE_STOP,  0);  if (time_in_state >= 150) g_scan_dist_C = dist; }
            else if (time_in_state < 800)  { go(DRIVE_LEFT,  95); }
            else if (time_in_state < 1100) { go(DRIVE_STOP,  0);  g_scan_dist_L = dist; }
            else if (time_in_state < 2300) { go(DRIVE_RIGHT, 95); }
            else if (time_in_state < 2600) { go(DRIVE_STOP,  0);  g_scan_dist_R = dist; }
            else if (time_in_state < 3100) { go(DRIVE_LEFT,  95); }
            else { go(DRIVE_STOP, 0); enter(EXPLORE_CHOOSE, now_ms); }
            break;
        }

        // ── CHOOSE: one-shot decision based on scan data + randomness ─────────
        case EXPLORE_CHOOSE: {
            if (time_in_state < 300) break;

            if (!g_choose_decided) {
                g_choose_decided = true;

                Serial.print("[EXPLORE] C="); Serial.print(g_scan_dist_C);
                Serial.print(" L="); Serial.print(g_scan_dist_L);
                Serial.print(" R="); Serial.println(g_scan_dist_R);

                // Blocked = within sensor read range (330mm)
                bool c_blocked = (g_scan_dist_C < EXPLORE_SCAN_RANGE);
                bool l_blocked = (g_scan_dist_L < EXPLORE_SCAN_RANGE);
                bool r_blocked = (g_scan_dist_R < EXPLORE_SCAN_RANGE);

                // If all truly impassable: U-turn
                if (g_scan_dist_C < EXPLORE_BLOCKED_DIST &&
                    g_scan_dist_L < EXPLORE_BLOCKED_DIST &&
                    g_scan_dist_R < EXPLORE_BLOCKED_DIST) {
                    enter(EXPLORE_UTURN, now_ms);
                    break;
                }

                // Random variety roll — applied regardless of direction
                uint8_t variety = (uint8_t)random(100);
                if (variety < 12) {
                    enter(EXPLORE_SILLY, now_ms);
                    break;
                } else if (variety < 28) {
                    g_wonder_exit = 0;
                    enter(EXPLORE_WONDER, now_ms);
                    break;
                } else if (variety < 45) {
                    enter(EXPLORE_UTURN, now_ms);
                    break;
                }
                // Else: pick a direction and drive

                // Direction: only use scan data to AVOID blocked sides.
                // Don't chase "optimal" — go forward unless centre is blocked.
                DriveDirection dir = DRIVE_FORWARD;
                if (c_blocked) {
                    // Centre blocked — turn away from blocked side
                    if (!l_blocked && r_blocked)       dir = DRIVE_LEFT;
                    else if (!r_blocked && l_blocked)  dir = DRIVE_RIGHT;
                    else if (!l_blocked && !r_blocked) dir = (random(2) == 0) ? DRIVE_LEFT : DRIVE_RIGHT;
                    else { enter(EXPLORE_UTURN, now_ms); break; }
                }
                // (if centre clear: go forward — ignore whether sides are tighter)

                if (dir != DRIVE_FORWARD) {
                    // Brief spin toward chosen direction, then drive
                    go(dir, 90);
                    // g_choose_decided stays true; time gate below transitions to DRIVING
                } else {
                    enter(EXPLORE_DRIVING, now_ms);
                }
            } else {
                // Brief pre-turn is running — wait 400ms then go
                if (time_in_state >= 700) enter(EXPLORE_DRIVING, now_ms);
            }
            break;
        }

        // ── DRIVING: move forward, watch for obstacles ────────────────────────
        case EXPLORE_DRIVING: {
            go(DRIVE_FORWARD, 100);

            // Reset stuck counter if drove cleanly for 5s
            if (now_ms - g_drive_start_ms >= EXPLORE_STUCK_WINDOW) {
                g_stuck_count = 0;
            }

            // Obstacle
            if (dist < EXPLORE_STOP_DIST && dist > 0) {
                handle_obstacle(now_ms);
                break;
            }

            // Person appeared (edge only)
            if (prox == PROXIMITY_NEARBY && g_last_prox == PROXIMITY_FAR) {
                if (chance_percent(40)) {
                    enter(EXPLORE_GREET, now_ms);
                } else {
                    enter(EXPLORE_SCAN, now_ms);
                }
                break;
            }

            // Spontaneous silly spin
            if (g_next_silly_ms > 0 && now_ms >= g_next_silly_ms) {
                enter(EXPLORE_SILLY, now_ms);
                break;
            }

            // Phase timeout → re-scan
            if (time_in_state >= 8000) {
                enter(EXPLORE_SCAN, now_ms);
                break;
            }
            break;
        }

        // ── BACKUP: reverse briefly ───────────────────────────────────────────
        case EXPLORE_BACKUP: {
            if (time_in_state >= g_backup_duration_ms) {
                if      (g_backup_exit == 1) enter(EXPLORE_UTURN,   now_ms);
                else if (g_backup_exit == 2) { g_wonder_exit = 0; enter(EXPLORE_WONDER, now_ms); }
                else if (g_backup_exit == 3) enter(EXPLORE_SILLY,   now_ms);
                else                         enter(EXPLORE_SCAN,    now_ms);
            }
            break;
        }

        // ── WONDER: stopped, "thinking" ───────────────────────────────────────
        case EXPLORE_WONDER: {
            if (time_in_state >= g_state_duration_ms) {
                if (g_wonder_exit == 1) {
                    // Greet (wave + happy chirp)
                    enter(EXPLORE_GREET, now_ms);
                } else if (g_wonder_exit == 2) {
                    // Short backup then silly spin
                    g_backup_duration_ms = 600;
                    g_backup_exit        = 3;  // → silly
                    enter(EXPLORE_BACKUP, now_ms);
                } else {
                    // Normal wonder exit — random
                    uint8_t roll = (uint8_t)random(100);
                    if      (roll < 35) enter(EXPLORE_SILLY,   now_ms);
                    else if (roll < 55) enter(EXPLORE_UTURN,   now_ms);
                    else                enter(EXPLORE_DRIVING,  now_ms);
                }
            }
            break;
        }

        // ── UTURN: spin ~180° ─────────────────────────────────────────────────
        case EXPLORE_UTURN: {
            go(g_uturn_dir, 110);
            if (time_in_state >= g_state_duration_ms) {
                enter(EXPLORE_DRIVING, now_ms);
            }
            break;
        }

        // ── SILLY: quick playful double-spin ──────────────────────────────────
        case EXPLORE_SILLY: {
            if      (time_in_state < 700)  go(DRIVE_LEFT,  110);
            else if (time_in_state < 1400) go(DRIVE_RIGHT, 110);
            else { go(DRIVE_STOP, 0); enter(EXPLORE_DRIVING, now_ms); }
            break;
        }

        // ── GREET: stopped, waving + smiling ─────────────────────────────────
        case EXPLORE_GREET: {
            if (time_in_state >= 3500) enter(EXPLORE_DRIVING, now_ms);
            break;
        }

        // ── TRAPPED: hit too many obstacles — angry standstill ───────────────
        case EXPLORE_TRAPPED: {
            if (time_in_state < 2000) {
                // Phase 1: angry spin
                uint32_t t = time_in_state % 400;
                go((t < 200) ? DRIVE_LEFT : DRIVE_RIGHT, 160);
            } else {
                // Phase 2: stopped, angry face — watch for someone approaching
                go(DRIVE_STOP, 0);

                uint16_t cur_dist = proximity_get_last_distance();
                if (cur_dist < g_trapped_dist_save && (g_trapped_dist_save - cur_dist) > 80) {
                    // Someone came closer — they want to help! go happy
                    g_stuck_count = 0;
                    enter(EXPLORE_GREET, now_ms);
                    break;
                }

                // Give up after 20s of staring
                if (time_in_state >= 22000) {
                    explore_quit();
                }
            }
            break;
        }

        default: break;
    }

    g_last_prox = prox;
}

void explore_handle_event(const Event *event) {
    if (g_state == EXPLORE_IDLE) return;
    switch (event->type) {
        case EVENT_MOTION_SHAKEN:
        case EVENT_MOTION_FLIPPED:
        case EVENT_SOUND_BURST:
            explore_quit();
            break;
        default:
            break;
    }
}
