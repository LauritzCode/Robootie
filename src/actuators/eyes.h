#pragma once

#include "interpreters/comfort_interpreter.h"
#include <stdint.h>

typedef enum
{
    EYES_MODE_SLEEP = 0,
    EYES_MODE_AWAKE
} EyesMode;


void eyes_init(void);
void eyes_set_mode(EyesMode mode);
void eyes_update(uint32_t now_ms);
void eyes_set_comfort_flags(ComfortFlags flags);
void apply_base_pose(void);
void apply_comfort_modifiers(void);
