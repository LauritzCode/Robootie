#pragma once
#include <stdint.h>

typedef enum SoundPatternID
{
    SOUND_NONE = 0,

    SOUND_BRIEF_REACT,
    SOUND_LAUGH,
    SOUND_SPOOK
} SoundPatternID;

typedef struct SoundIntent
{
    bool play;                 // Should actuator start playing
    SoundPatternID pattern;    // Which sound pattern to play
    uint8_t intensity;         // Future: emotional strength (0–255)
} SoundIntent;

const SoundIntent* system_controller_get_sound_intent(void);
