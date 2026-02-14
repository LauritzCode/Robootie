#include "sound_interpreter.h"
#include "core/event_queue.h"
#include "core/event.h"


static const uint32_t PEAK_WINDOW_MS = 1500;
static const uint32_t QUIET_WINDOW_MS = 2500;

static const uint8_t TALKING_PEAK_COUNT = 8;
static const uint8_t NOISE_PEAK_COUNT = 10;


static SoundFlags flags;


static uint32_t peak_times[12];
static uint8_t peak_count = 0;

static uint32_t last_peak_time = 0;

void sound_interpreter_init(void)
{
    flags.talking = false;
    flags.noise = false;
    flags.quiet = true;

    peak_count = 0;
    last_peak_time = 0;
}

static void cleanup_old_peaks(uint32_t now_ms)
{
    uint8_t new_count = 0;

    for (uint8_t i = 0; i < peak_count; i++)
    {
        if (now_ms - peak_times[i] <= PEAK_WINDOW_MS)
        {
            peak_times[new_count++] = peak_times[i];
        }
    }

    peak_count = new_count;
}

void sound_interpreter_handle_event(const Event *event)
{
    if (event->type != EVENT_SOUND_PEAK)
        return;

    uint32_t t = event->timestamp_ms;

    last_peak_time = t;

    if (peak_count < 12)
    {
        peak_times[peak_count++] = t;
    }
    else
    {
        // shift buffer left
        for (uint8_t i = 1; i < 12; i++)
            peak_times[i - 1] = peak_times[i];

        peak_times[11] = t;
    }
}

void sound_interpreter_update(uint32_t now_ms)
{
    cleanup_old_peaks(now_ms);

    uint8_t count = peak_count;

    bool talking_now = (count >= TALKING_PEAK_COUNT);
    bool noise_now   = (count >= NOISE_PEAK_COUNT);
    bool quiet_now   = (now_ms - last_peak_time >= QUIET_WINDOW_MS);

      if (talking_now && !flags.talking)
    {
        Event e;
        e.type = EVENT_SOUND_TALKING;
        e.timestamp_ms = now_ms;
        event_queue_push(e);
    }

        if (noise_now && !flags.noise)
    {
        Event e;
        e.type = EVENT_SOUND_GENERAL_NOISE;
        e.timestamp_ms = now_ms;
        event_queue_push(e);
    }

        flags.talking = talking_now;
        flags.noise = noise_now;
        flags.quiet = quiet_now;
}


SoundFlags sound_interpreter_get_flags(void)
{
    return flags;
}
