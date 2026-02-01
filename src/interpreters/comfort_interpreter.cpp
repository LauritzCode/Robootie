#include <Arduino.h>

#include "comfort_interpreter.h"
#include "config/thresholds.h"

static ComfortFlags flags;
static uint32_t hot_enter_time = 0;
static uint32_t cold_enter_time = 0;
static uint32_t last_hot_seen_time = 0;
static uint32_t last_cold_seen_time = 0;


void comfort_interpreter_init(void)
{
    flags.overheated = false;
    flags.chilled = false;
}

void comfort_interpreter_update(uint32_t now_ms)
{
    if(flags.hot) {
        last_hot_seen_time = now_ms;

        if(!flags.overheated && (now_ms - hot_enter_time) >= HOT_CONFIRM_MS) {
            flags.overheated = true;
            Serial.println("Is too hot :(.");
        }
    } else {

        if(flags.overheated) {
            if((now_ms - last_hot_seen_time) >= HOT_GRACE_MS) {
                flags.overheated = false; 
                last_hot_seen_time = 0;
                hot_enter_time = 0;
            }
        } else {
            if((now_ms - last_hot_seen_time) >= HOT_GRACE_MS) {
                last_hot_seen_time = 0;
                hot_enter_time = 0;
        }
    }
 }


    if(flags.cold) {
            last_cold_seen_time = now_ms;

            if(!flags.chilled && (now_ms - cold_enter_time) >= CHILL_CONFIRM_MS) {
                flags.chilled = true;
                Serial.println("Is too cold :(.");
            }
        } else {

            if(flags.chilled) {
                if((now_ms - last_cold_seen_time) >= CHILL_GRACE_MS) {
                    flags.chilled = false; 
                    last_cold_seen_time = 0;
                    cold_enter_time = 0;
                }
            } else {
                if((now_ms - last_cold_seen_time) >= CHILL_GRACE_MS) {
                    last_cold_seen_time = 0;
                    cold_enter_time = 0;
            }
        }
    }

}

void comfort_interpreter_handle_event(const Event *event)
{
    switch (event->type)
    {
        case EVENT_TEMP_ENTER_HOT:
            flags.hot = true;
            hot_enter_time = event->timestamp_ms;
            last_hot_seen_time = event->timestamp_ms;
            break;

        case EVENT_TEMP_EXIT_HOT:
            flags.hot = false;
            break;

        case EVENT_TEMP_ENTER_COLD:
            flags.cold = true;
            cold_enter_time = event->timestamp_ms;
            last_cold_seen_time = event->timestamp_ms;
            break;

        case EVENT_TEMP_EXIT_COLD:
            flags.cold = false;
            break;

        default:
            break;
    }
}

ComfortFlags comfort_interpreter_get_flags(void)
{
    return flags;
}