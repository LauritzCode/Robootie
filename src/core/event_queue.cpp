#include "event_queue.h"

#define EVENT_QUEUE_SIZE 8 

static Event event_buffer[EVENT_QUEUE_SIZE];
static uint8_t head = 0;
static uint8_t tail = 0;
static uint8_t count = 0;

void event_queue_init(void) {

    head = 0;
    tail = 0;
    count = 0;
}

bool event_queue_push(Event event) {

    if(count >= EVENT_QUEUE_SIZE) {
        return false;
    }

    event_buffer[tail] = event;
    tail = (tail + 1) % EVENT_QUEUE_SIZE;
    count++;

    return true;
}

bool event_queue_pop(Event *event_out) {
    if(count == 0) {
        return false;
    }

    *event_out = event_buffer[head];
    head = (head + 1) % EVENT_QUEUE_SIZE;
    count--;

    return true;
}