#include "event_dispatcher.h"
#include "core/event_queue.h"
#include "brain/behavior_fsm.h"
#include "interpreters/comfort_interpreter.h"
#include "interpreters/light_interpreter.h"
#include "system/system_controller.h"
#include "interpreters/emotion_interpreter.h"



void dispatch_events(void) {
        
    Event event;

 while (event_queue_pop(&event))
    {
        behavior_fsm_handle_event(&event);
        system_controller_handle_event(&event);
        comfort_interpreter_handle_event(&event);
        light_interpreter_handle_event(&event);
        emotion_interpreter_handle_event(&event);
    }
}