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