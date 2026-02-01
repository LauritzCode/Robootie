#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "core/event.h"
#include "system/system_controller.h"

typedef struct
{
    bool overheated;
    bool chilled;
} ComfortFlags;

void comfort_interpreter_init(void);
void comfort_interpreter_update(uint32_t now_ms);

void comfort_interpreter_handle_event(const Event *event);
ComfortFlags comfort_interpreter_get_flags(void);