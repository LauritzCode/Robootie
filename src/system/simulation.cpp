#include <Arduino.h>

#include "simulation.h"
#include "core/event_queue.h"

static bool demo_fired = false;
static uint32_t startup_time = 0;

void simulation_init(void)
{
    startup_time = 0;
    demo_fired = false;
}

void simulation_push_event(EventType type, uint32_t now_ms)
{
    Event e = {};
    e.type = type;
    e.timestamp_ms = now_ms;

    event_queue_push(e);
    Serial.println("Event now pushed");
}


