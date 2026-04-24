#pragma once

#include <stdint.h>

typedef enum
{
    LIGHT_STATE_DARK = 0,
    LIGHT_STATE_SEMI_BRIGHT,
    LIGHT_STATE_BRIGHT,
    LIGHT_STATE_TOO_BRIGHT
} LightState;

void light_sensor_init(void);
void light_sensor_update(uint32_t now_ms);
int light_sensor_read_raw(void);
