#pragma once

#include <stdint.h>
#include "core/event.h"

typedef enum {
    ARMS_IDLE = 0, 
    ARMS_WAVE, 
    ARMS_GOF_OUT, 
    ARMS_DANCE, 
    ARMS_ATTACK, 
} ArmsPose;



typedef struct {
    ArmsPose pose;
    bool one_shot;  // true = do once and return to idle
                    // false = hold until intent changes
} ArmsIntent;


void arms_init(void);
void arms_update(uint32_t now_ms);
void arms_handle_event(const Event *event);
void arms_set_intent(const ArmsIntent *intent);