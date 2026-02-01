#pragma once

#include "interpreters/comfort_interpreter.h"
#include "interpreters/light_interpreter.h"
#include <stdint.h>
#include "eyes_intent.h"
#include "config/thresholds.h"

typedef enum
{
    EYES_MODE_SLEEP = 0,
    EYES_MODE_AWAKE
} EyesMode;


void eyes_init(void);
void eyes_set_mode(EyesMode mode);
void eyes_set_intent(const EyesIntent *intent);
void eyes_update(uint32_t now_ms);
void eyes_set_temp_comfort_flags(ComfortFlags flags);
void eyes_set_light_comfort_flags(LightFlags flags);
void apply_base_pose(void);
void apply_comfort_modifiers(void);



void apply_base_sleep(void);
void apply_base_awake(void);
void apply_base_half_awake(void);
void apply_modifiers(const EyesIntent*);