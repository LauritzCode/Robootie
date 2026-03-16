#pragma once 
#include "core/event.h"

typedef struct {
    bool too_close;
    bool nearby;
    bool clear;
} ProximityFlags;

void proximity_interpreter_init(void);
void proximity_interpreter_handle_event(const Event *event);
ProximityFlags proximity_interpreter_get_flags(void);