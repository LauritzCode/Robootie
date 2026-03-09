#include <Arduino.h>
#include "sound_sensor.h"
#include "core/event_queue.h"
#include "core/event.h"
#include "config/pins.h"

// ── thresholds ────────────────────────────────────────────────────────────────
static const int NOISE_THRESHOLD      = 10;
static const int PEAK_THRESHOLD       = 25;
static const int BURST_THRESHOLD      = 250;

static const uint32_t PEAK_MIN_DURATION_MS  = 20;
static const uint32_t BURST_COOLDOWN_MS     = 600;

// ── baseline calibration ──────────────────────────────────────────────────────
static const uint32_t CALIBRATION_DURATION_MS = 1500;  // sample for 1.5s on boot
static const uint32_t DRIFT_INTERVAL_MS       = 5000;  // recalibrate drift every 5s

static int      baseline             = 512;   // fallback until calibrated
static bool     calibrated           = false;
static uint32_t calibration_start    = 0;
static int32_t  calibration_sum      = 0;
static uint16_t calibration_count    = 0;

static uint32_t last_drift_time      = 0;
static int32_t  drift_sum            = 0;
static uint16_t drift_count          = 0;

// ── peak tracking ─────────────────────────────────────────────────────────────
static bool     in_peak          = false;
static int      peak_max_value   = 0;
static uint32_t peak_start_time  = 0;
static uint32_t last_burst_time  = 0;


void sound_sensor_init(void)
{
    pinMode(AUDIO_ANALOG_PIN, INPUT);
    calibration_start = millis();
}

void sound_sensor_update(uint32_t now_ms)
{
    int raw = analogRead(AUDIO_ANALOG_PIN);

    // ── phase 1: boot calibration ─────────────────────────────────────────────
    if (!calibrated)
    {
        calibration_sum   += raw;
        calibration_count++;

        if (now_ms - calibration_start >= CALIBRATION_DURATION_MS)
        {
            baseline    = (int)(calibration_sum / calibration_count);
            calibrated  = true;
            last_drift_time = now_ms;
        }

        return;   // don't process peaks during calibration
    }

    // ── phase 2: slow drift correction ───────────────────────────────────────
    // accumulate quiet samples and nudge baseline toward them every 5s
    int delta_check = raw - baseline;
    if (delta_check < 0) delta_check = -delta_check;

    if (delta_check < NOISE_THRESHOLD)   // only use truly quiet samples
    {
        drift_sum   += raw;
        drift_count++;
    }

    if (now_ms - last_drift_time >= DRIFT_INTERVAL_MS && drift_count > 10)
    {
        int new_baseline = (int)(drift_sum / drift_count);
        // nudge baseline slowly — don't jump suddenly
        baseline        = (baseline * 3 + new_baseline) / 4;
        drift_sum       = 0;
        drift_count     = 0;
        last_drift_time = now_ms;
    }

    // ── phase 3: peak detection ───────────────────────────────────────────────
    int delta = raw - baseline;
    if (delta < 0) delta = 0;

    if (!in_peak)
    {
        if (delta > PEAK_THRESHOLD)
        {
            in_peak         = true;
            peak_start_time = now_ms;
            peak_max_value  = delta;
        }
        return;
    }

    if (delta > peak_max_value)
        peak_max_value = delta;

    if (delta < NOISE_THRESHOLD)
    {
        uint32_t peak_duration = now_ms - peak_start_time;

        if (peak_duration >= PEAK_MIN_DURATION_MS)
        {
            // send peak with amplitude
            Event peak_event;
            peak_event.type         = EVENT_SOUND_PEAK;
            peak_event.timestamp_ms = now_ms;
            peak_event.value        = (uint16_t)peak_max_value;  // ← amplitude
            event_queue_push(peak_event);

            // burst check
            if (peak_max_value > BURST_THRESHOLD &&
                now_ms - last_burst_time > BURST_COOLDOWN_MS)
            {
                Event burst_event;
                burst_event.type         = EVENT_SOUND_BURST;
                burst_event.timestamp_ms = now_ms;
                burst_event.value        = (uint16_t)peak_max_value;
                event_queue_push(burst_event);
                last_burst_time = now_ms;
            }
        }

        in_peak        = false;
        peak_max_value = 0;
    }
}