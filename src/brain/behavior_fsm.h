#pragma once 

#include "core/event.h"

typedef enum
{
    BEHAVIOR_ASLEEP = 0,
    BEHAVIOR_AWAKE,
    BEHAVIOR_BORED,
    BEHAVIOR_EXPLORE
} BehaviorState;


void behavior_fsm_init(void);

void behavior_fsm_handle_event(const Event *event);

BehaviorState behavior_fsm_get_state(void);

void handle_asleep_state(const Event *event);
void handle_awake_state(const Event *event);
void handle_bored_state(const Event *event);
void behavior_fsm_set_state(BehaviorState state);