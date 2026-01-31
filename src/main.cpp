#include <Arduino.h>

#include "core/event_queue.h"
#include "brain/behavior_fsm.h"
#include "sensors/light_sensor.h"
#include "actuators/eyes.h"
#include "system/system_controller.h"

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

    system_controller_update(now);
    eyes_update(now);
}