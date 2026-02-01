#include "event_dispatcher.h"
#include "core/event_queue.h"
#include "brain/behavior_fsm.h"
<<<<<<< HEAD
#include "interpreters/comfort_interpreter.h"

=======
#include "system/system_controller.h"
>>>>>>> fdd4fe08416134d877b87189b80a1a5fc0c83211

void dispatch_events(void) {
        
    Event event;

 while (event_queue_pop(&event))
    {
        behavior_fsm_handle_event(&event);
        system_controller_handle_event(&event);
        comfort_interpreter_handle_event(&event);
    }
}