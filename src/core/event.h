#pragma once 
#include <stdint.h>

/*

Event type. Represents meaningful changes in the robot's world.
Events are produced by sensors and consumed by the brain. (FSM)

*/

typedef enum {
    EVENT_NONE = 0,

    // Light-related events 
    EVENT_LIGHT_BECAME_DARK,
    EVENT_LIGHT_BECAME_BRIGHT,

    // More events to come 
} EventType;

typedef struct
{
    EventType type;
    uint32_t timestamp_ms;
} Event;

