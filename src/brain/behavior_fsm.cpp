#include "behavior_fsm.h"
#include <Arduino.h>

static BehaviorState current_state;
static bool bored_sleep = false;


void behavior_fsm_init(void) {
    current_state = BEHAVIOR_AWAKE;
    Serial.println("FSM init: ASLEEP");
}

BehaviorState behavior_fsm_get_state(void) {
    return current_state;
}

void behavior_fsm_handle_event(const Event *event) {
    switch(current_state) {
        case BEHAVIOR_ASLEEP:
        handle_asleep_state(event);
        break;

        case BEHAVIOR_AWAKE: 
        handle_awake_state(event);
        break;
        case BEHAVIOR_BORED:
        handle_bored_state(event);
        break;
        case BEHAVIOR_EXPLORE:
        // transitions managed by explore.cpp
        break;
        default:
        break;
    }
}

// State handlers

 void handle_asleep_state(const Event *event) {
    switch (event->type) {
        case EVENT_LIGHT_BECAME_BRIGHT:
            if (!bored_sleep)
                current_state = BEHAVIOR_AWAKE;
            break;
        default:
            break;
    }
}

 void handle_awake_state(const Event *event)
{
    switch (event->type)
    {
        case EVENT_LIGHT_BECAME_DARK:
            current_state = BEHAVIOR_ASLEEP;
            Serial.println("FSM: AWAKE -> ASLEEP");
            break;

        default:
            /* Ignore all other events */
            break;
    }
}

void handle_bored_state(const Event *event) {
    switch (event->type) {
        case EVENT_LIGHT_BECAME_BRIGHT:
            current_state = BEHAVIOR_AWAKE;
            break;
        default:
            break;
    }
}

void behavior_fsm_set_state(BehaviorState state) {
    if (state == BEHAVIOR_ASLEEP && current_state == BEHAVIOR_BORED)
        bored_sleep = true;
    if (state == BEHAVIOR_AWAKE)
        bored_sleep = false;
    current_state = state;
}