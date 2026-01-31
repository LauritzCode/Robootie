#pragma once 
#include <stdint.h>

/*

Event type. Represents meaningful changes in the robot's world.
Events are produced by sensors and consumed by the brain. (FSM)

*/

typedef enum {
    EVENT_NONE = 0,

    // Light related events 
    EVENT_LIGHT_BECAME_DARK,
    EVENT_LIGHT_BECAME_BRIGHT,

    // Temp related events
    EVENT_TEMP_ENTER_COLD,
    EVENT_TEMP_EXIT_COLD,

    EVENT_TEMP_ENTER_COMFY,
    EVENT_TEMP_EXIT_COMFY,

    EVENT_TEMP_ENTER_HOT,
    EVENT_TEMP_EXIT_HOT,

} EventType;

typedef struct
{
    EventType type;
    uint32_t timestamp_ms;
} Event;

