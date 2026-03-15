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
    MOUTH_SLEEPY_ANNOYED,
    MOUTH_GREETING,
    MOUTH_PERSONAL_SPACE,
    MOUTH_GOODBYE,
    MOUTH_LINGERING,
    MOUTH_BORED
} MouthDisplay;

static MouthDisplay g_current  = MOUTH_IDLE;
static MouthDisplay g_transient = MOUTH_IDLE;   
static ActionTimer  g_transient_timer;

#define TRANSIENT_DURATION_MS 3000  


static void lcd_print2(const char *line1, const char *line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print((__FlashStringHelper*)line1);
    lcd.setCursor(0, 1);
    lcd.print((__FlashStringHelper*)line2);
}

static void render_expr(const LcdExpr *arr, uint8_t count) {
    uint8_t i = random_index(count);
    const char* l1 = (const char*)pgm_read_ptr(&arr[i].line1);
    const char* l2 = (const char*)pgm_read_ptr(&arr[i].line2);
    lcd_print2(l1, l2);
}


static void render(MouthDisplay d) {
    switch (d) {
        case MOUTH_IDLE:
            lcd.clear();
            break;
        case MOUTH_SOUND_BURST:
            render_expr(burst_expressions, BURST_EXPR_COUNT);
            break;
        case MOUTH_TEMP_EXIT_HOT:
            render_expr(exit_hot_expressions, EXIT_HOT_EXPR_COUNT);
            break;
        case MOUTH_TEMP_ENTER_COMFY:
            render_expr(enter_comfy_expressions, ENTER_COMFY_EXPR_COUNT);
            break;
        case MOUTH_TEMP_EXIT_COLD:
            render_expr(exit_cold_expressions, EXIT_COLD_EXPR_COUNT);
            break;
        case MOUTH_OVERHEATED:
            render_expr(overheated_expressions, OVERHEATED_EXPR_COUNT);
            break;
        case MOUTH_CHILLED:
            render_expr(chilled_expressions, CHILLED_EXPR_COUNT);
            break;
        case MOUTH_HOT:
            render_expr(hot_expressions, HOT_EXPR_COUNT);
            break;
        case MOUTH_COLD:
            render_expr(cold_expressions, COLD_EXPR_COUNT);
            break;
        case MOUTH_TALKING:
            render_expr(talking_expressions, TALKING_EXPR_COUNT);
            break;
        case MOUTH_NOISE:
            render_expr(noise_expressions, NOISE_EXPR_COUNT);
            break;
        case MOUTH_MUSIC:
            render_expr(music_expressions, MUSIC_EXPR_COUNT);
            break;
        case MOUTH_SLEEPY_ANNOYED:
            render_expr(sleepy_annoyed_expressions, SLEEPY_ANNOYED_EXPR_COUNT);
            break;
        case MOUTH_GREETING:
            render_expr(greeting_expressions, GREETING_EXPR_COUNT);
        break;
        case MOUTH_PERSONAL_SPACE:
            render_expr(personal_space_expressions, PERSONAL_SPACE_EXPR_COUNT);
        break;
        case MOUTH_GOODBYE:
            render_expr(goodbye_expressions, GOODBYE_EXPR_COUNT);
        break;
        case MOUTH_LINGERING:
            render_expr(lingering_expressions, LINGERING_EXPR_COUNT);
        break;
        case MOUTH_BORED:
        render_expr(bored_expressions, BORED_EXPR_COUNT);
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

   static bool boot_shown = false;
    static bool boot_cleared = false;

    if (now_ms < 8000) {
        if (!boot_shown) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Hello!");
            lcd.setCursor(0, 1);
            lcd.print("I'm Robootie!");
            boot_shown = true;
        }
        return;
    }

    // first frame after boot — clear and reset state
    if (!boot_cleared) {
        lcd.clear();
        g_current = MOUTH_IDLE;
        boot_cleared = true;
    }

    // 1. expire transient if its timer has run out
    if (g_transient != MOUTH_IDLE && !timer_active(&g_transient_timer, now_ms)) {
        g_transient = MOUTH_IDLE;
    }

    // 2. get current context
    BehaviorContext ctx = system_controller_get_context();
    BehaviorState carc = behavior_fsm_get_state();
    // 3. resolve what should be showing
    MouthDisplay desired = MOUTH_IDLE;

    if (g_transient != MOUTH_IDLE) {
        // transient always wins
        desired = g_transient;

    } else if (ctx == CONTEXT_CONVERSING) {
        if(carc == BEHAVIOR_ASLEEP) {
            desired = MOUTH_SLEEPY_ANNOYED;
        } else {
            desired = MOUTH_TALKING;
        }
        // robot waited for quiet, now responds
        

    } else if (ctx == CONTEXT_ANNOYED) {
        // noise reaction driven by context, not raw flag
        desired = MOUTH_NOISE;

    } else if (ctx == CONTEXT_LINGERING) {
    desired = MOUTH_LINGERING;
} else if (ctx == CONTEXT_BORED) {
    desired = MOUTH_BORED;
} else {
        // comfort flags (highest sustained priority)
        ComfortFlags comfort = comfort_interpreter_get_flags();
        if      (comfort.overheated) desired = MOUTH_OVERHEATED;
        else if (comfort.chilled)    desired = MOUTH_CHILLED;
        else if (comfort.hot)        desired = MOUTH_HOT;
        else if (comfort.cold)       desired = MOUTH_COLD;

        // sound flags (only music remains here, 
        // talking and noise are handled by context above)
        else {
            SoundFlags sound = sound_interpreter_get_flags();
            if (sound.music) desired = MOUTH_MUSIC;
        }
    }

    // 4. apply — clears automatically when state changes to MOUTH_IDLE
    set_display(desired);
}


void mouth_handle_event(const Event *event) {
    // Events trigger transient messages that override everything for a fixed time.
    // "Most recent wins": a newer event always replaces the current transient.

    uint32_t now = millis();
    MouthDisplay next_transient = MOUTH_IDLE;

    switch (event->type) {
        case EVENT_TEMP_EXIT_HOT:         next_transient = MOUTH_TEMP_EXIT_HOT;    break;
        case EVENT_TEMP_ENTER_COMFY:      next_transient = MOUTH_TEMP_ENTER_COMFY; break;
        case EVENT_TEMP_EXIT_COLD:        next_transient = MOUTH_TEMP_EXIT_COLD;   break;
        case EVENT_SOUND_BURST:           next_transient = MOUTH_SOUND_BURST;      break;
        case EVENT_SOUND_GENERAL_NOISE:   next_transient = MOUTH_NOISE;            break;
        case EVENT_PROX_CLOSE:            next_transient = MOUTH_GREETING;         break;
        case EVENT_PROX_TOO_CLOSE:        next_transient = MOUTH_PERSONAL_SPACE;   break;
        case EVENT_PROX_FAR:              next_transient = MOUTH_GOODBYE;          break;
        default: return;
    }

    g_transient = next_transient;
    timer_start(&g_transient_timer, now, TRANSIENT_DURATION_MS);

    // render immediately so there's no one-loop delay
    g_current = MOUTH_IDLE;  // force set_display to re-render
    set_display(g_transient);
}

