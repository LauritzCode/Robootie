#include <Arduino.h>
#include "sound_sensor.h"
#include "core/event_queue.h"
#include "core/event.h"
#include "config/pins.h"

static const int BASELINE = 550;          // Temporary fixed baseline
static const int NOISE_THRESHOLD = 10;    // Ignore tiny fluctuations
static const int PEAK_THRESHOLD = 25;     // Start of peak
static const int BURST_THRESHOLD = 250;   // Loud sudden burst

static const uint32_t PEAK_MIN_DURATION_MS = 20;
static const uint32_t BURST_COOLDOWN_MS = 600;

static bool in_peak = false;
static int peak_max_value = 0;
static uint32_t peak_start_time = 0;
static uint32_t last_burst_time = 0;



void sound_sensor_init(void)
{
    pinMode(AUDIO_ANALOG_PIN, INPUT);
}

void sound_sensor_update(uint32_t now_ms)
{
    int raw = analogRead(AUDIO_ANALOG_PIN);
    int delta = raw - BASELINE;

    if (delta < 0)
        delta = 0;

    if (!in_peak)
    {
        if (delta > PEAK_THRESHOLD)
        {
            in_peak = true;
            peak_start_time = now_ms;
            peak_max_value = delta;
        }

        return;
    }

    if (delta > peak_max_value)
    {
        peak_max_value = delta;
    }

        if (delta < NOISE_THRESHOLD)
    {
        uint32_t peak_duration = now_ms - peak_start_time;

        if (peak_duration >= PEAK_MIN_DURATION_MS) {
            Event peak_event;
            peak_event.type = EVENT_SOUND_PEAK;
            peak_event.timestamp_ms = now_ms;
            event_queue_push(peak_event);

            if (peak_max_value > BURST_THRESHOLD &&
                now_ms - last_burst_time > BURST_COOLDOWN_MS)
            {
                Event burst_event;
                burst_event.type = EVENT_SOUND_BURST;
                burst_event.timestamp_ms = now_ms;
                event_queue_push(burst_event);

                last_burst_time = now_ms;
            }
        }


        in_peak = false;
        peak_max_value = 0;
    }
}
 