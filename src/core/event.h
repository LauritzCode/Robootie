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
    EVENT_LIGHT_BECAME_SEMI_BRIGHT,
    EVENT_LIGHT_BECAME_TOO_BRIGHT,

    // Temp related events
    EVENT_TEMP_ENTER_COLD,
    EVENT_TEMP_EXIT_COLD,

    EVENT_TEMP_ENTER_COMFY,
    EVENT_TEMP_EXIT_COMFY,

    EVENT_TEMP_ENTER_HOT,
    EVENT_TEMP_EXIT_HOT,

    // Sound related events

    EVENT_SOUND_BURST,
    EVENT_SOUND_TALKING,
    EVENT_SOUND_PEAK,
    EVENT_SOUND_MUSIC_DETECTED,
    EVENT_SOUND_GENERAL_NOISE,

    // Proximity related events

    EVENT_PROX_FAR,
    EVENT_PROX_CLOSE,
    EVENT_PROX_TOO_CLOSE,

    // Motion related events

    EVENT_MOTION_SHAKEN,
    EVENT_MOTION_PICKED_UP,
    EVENT_MOTION_PUT_DOWN,
    EVENT_MOTION_FLIPPED

} EventType;

typedef struct
{
    EventType type;
    uint32_t timestamp_ms;
    uint16_t value;
} Event;

