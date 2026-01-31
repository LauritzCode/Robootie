#include "event_dispatcher.h"
#include "core/event_queue.h"
#include "brain/behavior_fsm.h"

void dispatch_events(void) {
        
    Event event;

 if (event_queue_pop(&event))
    {
        behavior_fsm_handle_event(&event);
    }
}