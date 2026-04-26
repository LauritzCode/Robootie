#pragma once

#include <stdint.h>

typedef enum
{
    PROXIMITY_FAR = 0,
    PROXIMITY_NEARBY,
    PROXIMITY_TOO_CLOSE,
} ProximityState;

void proximity_init(void);
void proximity_update(uint32_t now_ms);
uint16_t proximity_get_last_distance(void);
ProximityState proximity_get_state(void);