#pragma once

#include <stdint.h>

void light_sensor_init(void);

void light_sensor_update(uint32_t now_ms);
