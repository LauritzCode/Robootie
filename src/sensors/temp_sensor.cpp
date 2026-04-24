#include <Arduino.h>
#include "temp_sensor.h"
#include "core/event.h"
#include "core/event_queue.h"
#include "config/pins.h"
#include "config/thresholds.h"


static TempState current_state;

static uint32_t last_sample_time = 0;
static const uint32_t SAMPLE_PERIOD_MS = 1000;

uint16_t Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

static float temp_detect() {

    Vo = analogRead(TEMP_SENSOR_PIN);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
    Tc = (T - 273.15); // Temperature in Celsius
   
    return Tc;
}

static TempState classify_temp(int raw)
{
    if (raw < TEMP_COLD_THRESHOLD)
        return TEMP_COLD;

    if (raw > TEMP_HOT_THRESHOLD)
        return TEMP_HOT;

    return TEMP_COMFY;
}

void temp_sensor_init(void) {
    pinMode(TEMP_SENSOR_PIN, INPUT);
    int raw = temp_detect();
    current_state = classify_temp(raw);

    last_sample_time = 0;

}

void temp_sensor_update(uint32_t now_ms) {
    if ((now_ms - last_sample_time) < SAMPLE_PERIOD_MS)
        return;

    last_sample_time = now_ms;
    int raw = temp_detect();
    TempState new_state = classify_temp(raw);

    if (new_state != current_state)
    {
        Event event;
        event.timestamp_ms = now_ms;

        // EXIT event 
        switch (current_state)
        {
            case TEMP_COLD:  event.type = EVENT_TEMP_EXIT_COLD;  break;
            case TEMP_COMFY: event.type = EVENT_TEMP_EXIT_COMFY; break;
            case TEMP_HOT:   event.type = EVENT_TEMP_EXIT_HOT;   break;
        }
        event_queue_push(event);

        // ENTER event
        switch (new_state)
        {
            case TEMP_COLD:  event.type = EVENT_TEMP_ENTER_COLD;  break;
            case TEMP_COMFY: event.type = EVENT_TEMP_ENTER_COMFY; break;
            case TEMP_HOT:   event.type = EVENT_TEMP_ENTER_HOT;   break;
        }
        event_queue_push(event);

        current_state = new_state;
    }

}

TempState temp_sensor_get_state(void) {
    return current_state;
}

float temp_sensor_read_celsius(void) {
    return temp_detect();
}