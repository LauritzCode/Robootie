#include "behavior_fsm.h"
#include <Arduino.h>

static BehaviorState current_state;

void behavior_fsm_init(void) {
    current_state = BEHAVIOR_ASLEEP;
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

        default: 
        // should never happen
        break;
    }
}

// State handlers

 void handle_asleep_state(const Event *event) {
    switch (event->type) {
        case EVENT_LIGHT_BECAME_BRIGHT:
        current_state = BEHAVIOR_AWAKE;
        Serial.println("FSM: ASLEEP -> AWAKE");
        break;

        default: 
              /* Ignore all other events */
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
