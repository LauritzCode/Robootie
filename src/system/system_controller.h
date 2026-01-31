#pragma once 

#include <stdint.h>
#include "core/event.h"


void system_controller_init(void);
void system_controller_update(uint32_t now_ms);
void system_controller_handle_event(const Event *event);