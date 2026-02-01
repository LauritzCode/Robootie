#include "light_sensor.h"
#include <Arduino.h>
#include "core/event.h"
#include "core/event_queue.h"
#include "config/pins.h"
#include "config/thresholds.h"

static LightState current_light_state;

static uint32_t last_sample_time = 0;
static const uint32_t SAMPLE_PERIOD_MS = 100;

void light_sensor_init(void)
{
    Event event;
    pinMode(LIGHT_SENSOR_PIN, INPUT);

    int raw = analogRead(LIGHT_SENSOR_PIN);

    if (raw <= LIGHT_TOO_BRIGHT_THRESHOLD)
    {
        current_light_state = LIGHT_STATE_TOO_BRIGHT;
        event.type = EVENT_LIGHT_BECAME_TOO_BRIGHT;
    }
    else if (raw <= LIGHT_SEMI_BRIGHT_THRESHOLD_MAX)
    {
        current_light_state = LIGHT_STATE_SEMI_BRIGHT;
        event.type = EVENT_LIGHT_BECAME_SEMI_BRIGHT;
    }
    else if (raw < LIGHT_DARK_THRESHOLD)
    {
        current_light_state = LIGHT_STATE_BRIGHT;
        event.type = EVENT_LIGHT_BECAME_BRIGHT;
    }
    else
    {
        current_light_state = LIGHT_STATE_DARK;
        event.type = EVENT_LIGHT_BECAME_DARK;
    }

    event.timestamp_ms = millis();
    event_queue_push(event);

    last_sample_time = event.timestamp_ms;
}


void light_sensor_update(uint32_t now_ms)
{
    if ((now_ms - last_sample_time) < SAMPLE_PERIOD_MS)
        return;

    last_sample_time = now_ms;

    int raw = analogRead(LIGHT_SENSOR_PIN);
    // Serial.println(raw);
    LightState new_state;

    /* Determine new state */
    if (raw <= LIGHT_TOO_BRIGHT_THRESHOLD)
    {
        new_state = LIGHT_STATE_TOO_BRIGHT;
    }
    else if (raw <= LIGHT_SEMI_BRIGHT_THRESHOLD_MAX && raw >= LIGHT_SEMI_BRIGHT_THRESHOLD_MIN)
    {
        new_state = LIGHT_STATE_SEMI_BRIGHT;
    }
    else if (raw < LIGHT_DARK_THRESHOLD)
    {
        new_state = LIGHT_STATE_BRIGHT;
    }
    else
    {
        new_state = LIGHT_STATE_DARK;
    }

    /* Edge detection */
    if (new_state != current_light_state)
    {
        Event event;
        event.timestamp_ms = now_ms;

        switch (new_state)
        {
            case LIGHT_STATE_DARK:
                event.type = EVENT_LIGHT_BECAME_DARK;
                break;

            case LIGHT_STATE_SEMI_BRIGHT:
                event.type = EVENT_LIGHT_BECAME_SEMI_BRIGHT;
                break;

            case LIGHT_STATE_TOO_BRIGHT:
                event.type = EVENT_LIGHT_BECAME_TOO_BRIGHT;
                break;

            case LIGHT_STATE_BRIGHT:
            default:
                event.type = EVENT_LIGHT_BECAME_BRIGHT;
                break;
        }

        event_queue_push(event);
        current_light_state = new_state;
    }
}
