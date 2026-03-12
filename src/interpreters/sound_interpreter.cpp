#include "sound_interpreter.h"
#include "core/event_queue.h"
#include "core/event.h"

// ── tuning constants ──────────────────────────────────────────────────────────
static const uint32_t PEAK_WINDOW_MS        = 1500;  // sliding window for peak counting
static const uint32_t QUIET_WINDOW_MS       = 2500;  // silence needed to go quiet
static const uint32_t MUSIC_COOLOFF_MS      = 3000;  // music flag stays alive this long after last detection
static const uint32_t MIN_INTERVALS_NEEDED  = 6;     // need at least this many gaps to judge regularity

static const uint8_t  TALKING_PEAK_MIN      = 3;     // min peaks in window to be talking
static const uint8_t  TALKING_PEAK_MAX      = 14;    // above this it's noise territory
static const uint8_t  NOISE_PEAK_COUNT      = 10;    // peaks in window to be noise

// music regularity: inter-peak interval variance must be below this (ms squared)
// lower = stricter, higher = more forgiving
static const uint32_t MUSIC_VARIANCE_THRESH = 12000;
// music needs peaks in this rate range (not too sparse, not too dense)
static const uint8_t  MUSIC_PEAK_MIN        = 8;
static const uint8_t  MUSIC_PEAK_MAX        = 18;

// ── state ─────────────────────────────────────────────────────────────────────
static SoundFlags flags;

static uint32_t peak_times[20];
static uint16_t peak_amps[20];      // amplitude of each peak in buffer
static uint8_t  peak_count  = 0;
static uint32_t last_peak_time = 0;
static uint32_t music_last_detected = 0;  // timestamp of last music detection


void sound_interpreter_init(void)
{
    flags.talking           = false;
    flags.noise             = false;
    flags.quiet             = true;
    flags.music             = false;

    peak_count              = 0;
    last_peak_time          = 0;
    music_last_detected     = 0xFFFFFFFF - MUSIC_COOLOFF_MS - 1;  // ← fix
}

// ── helpers ───────────────────────────────────────────────────────────────────

static void cleanup_old_peaks(uint32_t now_ms)
{
    uint8_t new_count = 0;
    for (uint8_t i = 0; i < peak_count; i++)
    {
        if (now_ms - peak_times[i] <= PEAK_WINDOW_MS)
        {
            peak_times[new_count] = peak_times[i];
            peak_amps[new_count]  = peak_amps[i];
            new_count++;
        }
    }
    peak_count = new_count;
}

// returns variance of inter-peak intervals in ms^2
// low variance = evenly spaced = music-like
static uint32_t calc_interval_variance(void)
{
    if (peak_count < MIN_INTERVALS_NEEDED + 1)
        return 0xFFFFFFFF;   // not enough data — return max to signal "unknown"

    // build intervals array
    uint32_t intervals[19];
    uint8_t  interval_count = peak_count - 1;

    for (uint8_t i = 0; i < interval_count; i++)
        intervals[i] = peak_times[i + 1] - peak_times[i];

    // mean
    uint32_t sum = 0;
    for (uint8_t i = 0; i < interval_count; i++)
        sum += intervals[i];
    uint32_t mean = sum / interval_count;

    // variance
    uint32_t var_sum = 0;
    for (uint8_t i = 0; i < interval_count; i++)
    {
        int32_t diff = (int32_t)intervals[i] - (int32_t)mean;
        var_sum += (uint32_t)(diff * diff);
    }

    return var_sum / interval_count;
}

// ── event handler ─────────────────────────────────────────────────────────────

void sound_interpreter_handle_event(const Event *event)
{
    if (event->type != EVENT_SOUND_PEAK)
        return;

    uint32_t t = event->timestamp_ms;
    last_peak_time = t;

    // push into circular buffer (max 20 slots)
    if (peak_count < 20)
    {
        peak_times[peak_count] = t;
        peak_amps[peak_count]  = event->value;
        peak_count++;
    }
    else
    {
        for (uint8_t i = 1; i < 20; i++)
        {
            peak_times[i - 1] = peak_times[i];
            peak_amps[i - 1]  = peak_amps[i];
        }
        peak_times[19] = t;
        peak_amps[19]  = event->value;
    }
}

// ── main update ───────────────────────────────────────────────────────────────

void sound_interpreter_update(uint32_t now_ms)
{
    cleanup_old_peaks(now_ms);

    uint8_t  count    = peak_count;
    bool     quiet_now = (now_ms - last_peak_time >= QUIET_WINDOW_MS);

    // ── noise: too many peaks, chaotic or not ────────────────────────────────
    bool noise_now = (count >= NOISE_PEAK_COUNT);

    // ── music: regular interval spacing, moderate peak rate ──────────────────
    bool music_now = false;
    if (!noise_now && count >= MUSIC_PEAK_MIN && count <= MUSIC_PEAK_MAX)
    {
        uint32_t variance = calc_interval_variance();
        if (variance < MUSIC_VARIANCE_THRESH)
        {
            music_now = true;
            music_last_detected = now_ms;
        }
    }

    // music cooloff — keep flag alive for MUSIC_COOLOFF_MS after last detection
    if (!music_now && (now_ms - music_last_detected < MUSIC_COOLOFF_MS))
        music_now = true;

    // ── talking: moderate peaks, not music, not noise ─────────────────────────
    bool talking_now = (!noise_now && !music_now &&
                        count >= TALKING_PEAK_MIN &&
                        count <= TALKING_PEAK_MAX);

    // ── fire transition events ────────────────────────────────────────────────
    if (talking_now && !flags.talking)
    {
        Event e;
        e.type         = EVENT_SOUND_TALKING;
        e.timestamp_ms = now_ms;
        e.value        = 0;
        event_queue_push(e);
    }

    if (noise_now && !flags.noise)
    {
        Event e;
        e.type         = EVENT_SOUND_GENERAL_NOISE;
        e.timestamp_ms = now_ms;
        e.value        = 0;
        event_queue_push(e);
    }

    if (music_now && !flags.music)
    {
        Event e;
        e.type         = EVENT_SOUND_MUSIC_DETECTED;
        e.timestamp_ms = now_ms;
        e.value        = 0;
        event_queue_push(e);
    }

    // ── apply ─────────────────────────────────────────────────────────────────
    flags.noise   = noise_now;
    flags.music   = music_now;
    flags.talking = talking_now;
    flags.quiet   = quiet_now;
}

SoundFlags sound_interpreter_get_flags(void)
{
    return flags;
}