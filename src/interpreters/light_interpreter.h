#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "core/event.h"

typedef struct
{
    bool dark;
    bool semi_bright;
    bool bright;
    bool too_bright;
} LightFlags;

void light_interpreter_init(void);
void light_interpreter_update(uint32_t now_ms);

void light_interpreter_handle_event(const Event *event);
LightFlags light_interpreter_get_flags(void);