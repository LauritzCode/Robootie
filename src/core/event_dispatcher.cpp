#include "event_dispatcher.h"
#include "core/event_queue.h"
#include "brain/behavior_fsm.h"
#include "interpreters/comfort_interpreter.h"
#include "interpreters/light_interpreter.h"
#include "system/system_controller.h"
#include "interpreters/emotion_interpreter.h"
#include "interpreters/sound_interpreter.h"
#include "actuators/mouth.h"
#include "actuators/arms.h"
#include "interpreters/proximity_interpreter.h"
#include "actuators/drive.h"

static bool is_manual_suppressed(const Event *e) {
    if (!drive_is_manual_active(e->timestamp_ms)) return false;
    switch (e->type) {
        case EVENT_MOTION_SHAKEN:
        case EVENT_MOTION_PICKED_UP:
        case EVENT_MOTION_PUT_DOWN:
        case EVENT_MOTION_FLIPPED:
        case EVENT_PROX_CLOSE:
        case EVENT_PROX_FAR:
        case EVENT_PROX_TOO_CLOSE:
        case EVENT_SOUND_BURST:
        case EVENT_SOUND_GENERAL_NOISE:
        case EVENT_SOUND_TALKING:
        case EVENT_SOUND_MUSIC_DETECTED:
            return true;
        default:
            return false;
    }
}

void dispatch_events(void) {

    Event event;

    while (event_queue_pop(&event))
    {
        if (is_manual_suppressed(&event)) continue;

        behavior_fsm_handle_event(&event);
        system_controller_handle_event(&event);
        comfort_interpreter_handle_event(&event);
        light_interpreter_handle_event(&event);
        emotion_interpreter_handle_event(&event);
        sound_interpreter_handle_event(&event);
        mouth_handle_event(&event);
        arms_handle_event(&event);
        proximity_interpreter_handle_event(&event);
    }
}