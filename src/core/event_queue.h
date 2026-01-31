#pragma once 

#include "event.h"
#include <stdbool.h>

/*
Event queue API. Single producer / single consumer FIFO
No dynamic memory
*/

void event_queue_init(void);

bool event_queue_push(Event event);

bool event_queue_pop(Event *event_out);