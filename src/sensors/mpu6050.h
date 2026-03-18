#pragma once
#include <stdint.h>

typedef struct {
    bool shaking;
    bool picked_up;
    bool flipped;   // true = upside down (AZ negative)
} MotionFlags;

void motion_sensor_init(void);
void motion_sensor_update(uint32_t now_ms);
MotionFlags motion_sensor_get_flags(void);
