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



void dispatch_events(void) {
        
    Event event;

 while (event_queue_pop(&event))
    {
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