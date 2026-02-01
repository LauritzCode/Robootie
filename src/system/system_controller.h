#pragma once 

#include <stdint.h>
#include "core/event.h"

typedef enum {
    COMFORT_COLD = 0,
    COMFORT_COMFY,
    COMFORT_HOT
} ComfortState;


typedef enum {
    INTENT_ALERT,
    INTENT_REST
} SystemIntent


void system_controller_init(void);
void system_controller_update(uint32_t now_ms);
void system_controller_handle_event(const Event *event);