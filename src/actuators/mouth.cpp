#include "mouth.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "system/system_controller.h"
#include "brain/behavior_fsm.h"
#include "actuators/eyes.h"
#include "core/event.h"
#include "core/timebase.h"
#include "config/thresholds.h"
#include "interpreters/comfort_interpreter.h"
#include "interpreters/light_interpreter.h"
#include "actuators/eyes_intent.h"
#include "interpreters/emotion_interpreter.h"
#include "actuators/sound_intent.h"
#include "brain/behavior_context.h"
#include "brain/data.h"
#include "interpreters/sound_interpreter.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);



typedef enum {
    MOUTH_IDLE = 0,

    // transient
    MOUTH_SOUND_BURST,       // "AH!!"
    MOUTH_TEMP_EXIT_HOT,     // "Phew...not so hot"
    MOUTH_TEMP_ENTER_COMFY,  // "is comfy"
    MOUTH_TEMP_EXIT_COLD,    // "Mmmm warm again!"

    // sustained (flag-driven, shown while flag is true)
    MOUTH_OVERHEATED,
    MOUTH_CHILLED,
    MOUTH_HOT,
    MOUTH_COLD,
    MOUTH_TALKING,
    MOUTH_NOISE,
    MOUTH_MUSIC,
} MouthDisplay;

static MouthDisplay g_current  = MOUTH_IDLE;
static MouthDisplay g_transient = MOUTH_IDLE;   
static ActionTimer  g_transient_timer;

#define TRANSIENT_DURATION_MS 3000  


static void lcd_print2(const char *line1, const char *line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}

static void render(MouthDisplay d) {
    uint8_t i;  // declared once, used in any case
    switch (d) {
        case MOUTH_IDLE:
            lcd.clear();
            break;
        case MOUTH_SOUND_BURST:
            i = random_index(BURST_EXPR_COUNT);
            lcd_print2(burst_expressions[i].line1, burst_expressions[i].line2);
            break;
        case MOUTH_TEMP_EXIT_HOT:
            i = random_index(EXIT_HOT_EXPR_COUNT);
            lcd_print2(exit_hot_expressions[i].line1, exit_hot_expressions[i].line2);
            break;
        case MOUTH_TEMP_ENTER_COMFY:
            i = random_index(ENTER_COMFY_EXPR_COUNT);
            lcd_print2(enter_comfy_expressions[i].line1, enter_comfy_expressions[i].line2);
            break;
        case MOUTH_TEMP_EXIT_COLD:
            i = random_index(EXIT_COLD_EXPR_COUNT);
            lcd_print2(exit_cold_expressions[i].line1, exit_cold_expressions[i].line2);
            break;
        case MOUTH_OVERHEATED:
            i = random_index(OVERHEATED_EXPR_COUNT);
            lcd_print2(overheated_expressions[i].line1, overheated_expressions[i].line2);
            break;
        case MOUTH_CHILLED:
            i = random_index(CHILLED_EXPR_COUNT);
            lcd_print2(chilled_expressions[i].line1, chilled_expressions[i].line2);
            break;
        case MOUTH_HOT:
            i = random_index(HOT_EXPR_COUNT);
            lcd_print2(hot_expressions[i].line1, hot_expressions[i].line2);
            break;
        case MOUTH_COLD:
            i = random_index(COLD_EXPR_COUNT);
            lcd_print2(cold_expressions[i].line1, cold_expressions[i].line2);
            break;
        case MOUTH_TALKING:
            i = random_index(TALKING_EXPR_COUNT);
            lcd_print2(talking_expressions[i].line1, talking_expressions[i].line2);
            break;
        case MOUTH_NOISE:
            i = random_index(NOISE_EXPR_COUNT);
            lcd_print2(noise_expressions[i].line1, noise_expressions[i].line2);
            break;
        case MOUTH_MUSIC:
            i = random_index(MUSIC_EXPR_COUNT);
            lcd_print2(music_expressions[i].line1, music_expressions[i].line2);
            break;
        default:
            lcd.clear();
            break;
    }
}

static void set_display(MouthDisplay next) {
    if (next == g_current) return;   // nothing changed, skip the I2C write
    g_current = next;
    render(next);
}


void mouth_init() {
    lcd.init();
    lcd.backlight();
}

void mouth_clear() {
    lcd.clear();
}

void mouth_update(uint32_t now_ms) {

    // 1. expire transient if its timer has run out
    if (g_transient != MOUTH_IDLE && !timer_active(&g_transient_timer, now_ms)) {
        g_transient = MOUTH_IDLE;
    }

    // 2. resolve what should be showing right now
    //    priority order (highest first):
    //      transient > comfort flags > sound flags > idle

    MouthDisplay desired = MOUTH_IDLE;

    if (g_transient != MOUTH_IDLE) {
        desired = g_transient;
    } else {
        // comfort flags
        ComfortFlags comfort = comfort_interpreter_get_flags();
        if      (comfort.overheated) desired = MOUTH_OVERHEATED;
        else if (comfort.chilled)    desired = MOUTH_CHILLED;
        else if (comfort.hot)        desired = MOUTH_HOT;
        else if (comfort.cold)       desired = MOUTH_COLD;

        SoundFlags sound = sound_interpreter_get_flags();
        if      (sound.talking) desired = MOUTH_TALKING;
        else if (sound.noise)   desired = MOUTH_NOISE;
        else if (sound.music)   desired = MOUTH_MUSIC;
    }

    // 3. apply — clears automatically when state changes to MOUTH_IDLE
    set_display(desired);
}

void mouth_handle_event(const Event *event) {
    // Events trigger transient messages that override everything for a fixed time.
    // "Most recent wins": a newer event always replaces the current transient.

    uint32_t now = millis();
    MouthDisplay next_transient = MOUTH_IDLE;

    switch (event->type) {
        case EVENT_TEMP_EXIT_HOT:         next_transient = MOUTH_TEMP_EXIT_HOT;   break;
        case EVENT_TEMP_ENTER_COMFY:      next_transient = MOUTH_TEMP_ENTER_COMFY; break;
        case EVENT_TEMP_EXIT_COLD:        next_transient = MOUTH_TEMP_EXIT_COLD;  break;
        case EVENT_SOUND_BURST:           next_transient = MOUTH_SOUND_BURST;     break;
        case EVENT_SOUND_GENERAL_NOISE:   next_transient = MOUTH_NOISE;           break;
        default: return;
    }

    g_transient = next_transient;
    timer_start(&g_transient_timer, now, TRANSIENT_DURATION_MS);

    // render immediately so there's no one-loop delay
    g_current = MOUTH_IDLE;  // force set_display to re-render
    set_display(g_transient);
}