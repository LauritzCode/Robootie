#pragma once 
#include <stdint.h>
#include "core/event.h"
typedef enum {
    DRIVE_STOP = 0,
    DRIVE_FORWARD,
    DRIVE_BACKWARD,
    DRIVE_LEFT,
    DRIVE_RIGHT,
    DRIVE_BRAKE
} DriveDirection;

typedef struct {
    DriveDirection direction;
    uint8_t speed;  // 0-255
} DriveIntent;

void drive_init(void);
void drive_update(uint32_t now_ms);
void drive_handle_event(const Event *event);
void drive_set_intent(const DriveIntent *intent);

// Test one motor in isolation at a fixed speed (0=FL, 1=FR, 2=RL, 3=RR)
void drive_test_motor(uint8_t which, uint8_t speed);