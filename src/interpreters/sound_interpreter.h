#pragma once
#include <stdint.h>
#include "core/event.h"

typedef struct
{
    bool talking;
    bool noise;
    bool quiet;
} SoundFlags;

void sound_interpreter_init(void);
void sound_interpreter_handle_event(const Event *event);
void sound_interpreter_update(uint32_t now_ms);

SoundFlags sound_interpreter_get_flags(void);
