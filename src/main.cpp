#include <Arduino.h>

#include "core/event_queue.h"
#include "brain/behavior_fsm.h"
#include "sensors/light_sensor.h"
#include "actuators/eyes.h"

void setup(void)
{
    Serial.begin(9600);

    event_queue_init();
    behavior_fsm_init();
    light_sensor_init();
    eyes_init();
}

void loop(void)
{
    uint32_t now = millis();

    light_sensor_update(now);

    Event event;

 if (event_queue_pop(&event))
    {
        behavior_fsm_handle_event(&event);
    }

    /* Map behavior → eye mode */
    if (behavior_fsm_get_state() == BEHAVIOR_ASLEEP)
    {
        eyes_set_mode(EYES_MODE_SLEEP);
    }
    else
    {
        eyes_set_mode(EYES_MODE_AWAKE);
    }

    eyes_update(now);
}