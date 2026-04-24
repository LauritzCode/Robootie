#pragma once 

#include <stdint.h>

typedef enum {
    TEMP_COMFY = 0,
    TEMP_HOT,
    TEMP_COLD
} TempState;


void temp_sensor_init(void);

void temp_sensor_update(uint32_t now_ms);

TempState temp_sensor_get_state(void);
float temp_sensor_read_celsius(void);