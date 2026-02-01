#include <Arduino.h>

#include "core/event_queue.h"
#include "core/event_dispatcher.h"
#include "brain/behavior_fsm.h"
#include "sensors/light_sensor.h"
#include "actuators/eyes.h"
#include "system/system_controller.h"
#include "sensors/temp_sensor.h"


void setup(void)
{
    Serial.begin(9600);

    event_queue_init();
    behavior_fsm_init();
    light_sensor_init();
    temp_sensor_init();
    eyes_init();
}

void loop(void)
{
    uint32_t now = millis();

    light_sensor_update(now);
    temp_sensor_update(now);
    dispatch_events();
    comfort_interpreter_update(now);
    system_controller_update(now);
    eyes_update(now);
}