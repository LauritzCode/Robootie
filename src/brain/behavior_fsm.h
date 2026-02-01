#pragma once 

#include "core/event.h"

typedef enum
{
    BEHAVIOR_ASLEEP = 0,
    BEHAVIOR_AWAKE
} BehaviorState;


void behavior_fsm_init(void);

void behavior_fsm_handle_event(const Event *event);

BehaviorState behavior_fsm_get_state(void);

static void handle_asleep_state(const Event *event);
static void handle_awake_state(const Event *event);