#include <Arduino.h>
#include "buzzer.h"
#include "config/pins.h"

struct ToneStep
{
    uint16_t frequency;
    uint16_t duration_ms;
};


static ToneStep pattern_buffer[8];
static uint8_t pattern_length = 0;
static uint8_t step_index = 0;

static bool playing = false;
static uint32_t last_step_time = 0;

static void generate_brief_react_pattern();
static void generate_laugh_pattern();
static void generate_spook_pattern();


void buzzer_apply_intent(const SoundIntent* intent)
{
    if (!intent->play)
        return;

    if (playing)
        return;  // simple priority for now

    switch(intent->pattern)
    {
        case SOUND_BRIEF_REACT:
            generate_brief_react_pattern();
            break;

        case SOUND_LAUGH:
            generate_laugh_pattern();
            break;

        case SOUND_SPOOK:
            generate_spook_pattern();
            break;

        default:
            return;
    }

    step_index = 0;
    playing = true;
    last_step_time = millis();

    tone(PIN_BUZZER, pattern_buffer[0].frequency);
}

void buzzer_update(uint32_t now_ms)
{
    if (!playing)
        return;

    if (now_ms - last_step_time >= pattern_buffer[step_index].duration_ms)
    {
        step_index++;
        last_step_time = now_ms;

        if (step_index >= pattern_length)
        {
            noTone(PIN_BUZZER);
            playing = false;
            return;
        }

        tone(PIN_BUZZER, pattern_buffer[step_index].frequency);
    }
}

bool buzzer_is_busy(void)
{
    return playing;
}




// 

static void generate_brief_react_pattern()
{
    pattern_length = 6;

    for (uint8_t i = 0; i < pattern_length; i++)
    {
        pattern_buffer[i].frequency = random(1200, 2500);
        pattern_buffer[i].duration_ms = random(60, 140);
    }
}

static void generate_laugh_pattern()
{
    pattern_length = 6;

    for (uint8_t i = 0; i < pattern_length; i++)
    {
        pattern_buffer[i].frequency = random(700, 1800);
        pattern_buffer[i].duration_ms = random(50, 120);
    }
}


static void generate_spook_pattern()
{
    pattern_length = 6;

    for (uint8_t i = 0; i < pattern_length; i++)
    {
        pattern_buffer[i].frequency = random(1500, 2600);
        pattern_buffer[i].duration_ms = random(10, 80);
    }
}
