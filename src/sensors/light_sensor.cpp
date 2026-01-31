#include "light_sensor.h"
#include <Arduino.h>
#include "core/event.h"
#include "core/event_queue.h"
#include "config/pins.h"
#include "config/thresholds.h"


typedef enum 
{
    LIGHT_STATE_DARK = 0,
    LIGHT_STATE_BRIGHT
} LightState;

static LightState current_light_state;

static uint32_t last_sample_time = 0;
static const uint32_t SAMPLE_PERIOD_MS = 100;


void light_sensor_init(void) {
    pinMode(LIGHT_SENSOR_PIN, INPUT);

    int raw = analogRead(LIGHT_SENSOR_PIN);

    current_light_state = (raw < LIGHT_DARK_THRESHOLD) ? LIGHT_STATE_BRIGHT : LIGHT_STATE_DARK;
    last_sample_time = 0;
}

void light_sensor_update(uint32_t now_ms) {
    if((now_ms - last_sample_time) < SAMPLE_PERIOD_MS) {
        return;
    }

    last_sample_time = now_ms;

    int raw = analogRead(LIGHT_SENSOR_PIN);

    LightState new_state = (raw < LIGHT_DARK_THRESHOLD) ? LIGHT_STATE_BRIGHT : LIGHT_STATE_DARK;
    

    if(new_state != current_light_state) {

        Event event;
        event.timestamp_ms = now_ms;

        if(new_state == LIGHT_STATE_DARK) {
            event.type = EVENT_LIGHT_BECAME_DARK;
        } else {
            event.type = EVENT_LIGHT_BECAME_BRIGHT;
        }

        event_queue_push(event);

        current_light_state = new_state;
    }
}