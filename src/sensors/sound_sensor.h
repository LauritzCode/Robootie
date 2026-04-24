#pragma once
#include <stdint.h>

void sound_sensor_init(void);
void sound_sensor_update(uint32_t now_ms);
int sound_sensor_read_raw(void);
