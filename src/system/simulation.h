#pragma once
#include <stdint.h>
#include "core/event.h"


void simulation_push_event(EventType type, uint32_t now_ms);


void simulation_init(void);
void simulation_update(uint32_t now_ms);
