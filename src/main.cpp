#include <Arduino.h>

#include "core/event_queue.h"
#include "core/event_dispatcher.h"
#include "brain/behavior_fsm.h"
#include "sensors/light_sensor.h"
#include "actuators/eyes.h"
#include "system/system_controller.h"
#include "system/simulation.h"
#include "sensors/temp_sensor.h"
#include "sensors/sound_sensor.h"
#include "interpreters/light_interpreter.h"
#include "interpreters/emotion_interpreter.h"
#include "interpreters/sound_interpreter.h"
#include "actuators/sound_intent.h"
#include "actuators/buzzer.h"
#include "actuators/mouth.h"
#include "actuators/arms.h"





void setup(void)
{
    Serial.begin(9600);

    event_queue_init();
    behavior_fsm_init();
    light_sensor_init();
    temp_sensor_init();
    light_interpreter_init();
    comfort_interpreter_init();
    eyes_init();
    mouth_init();
    armsTestInit();
}

void loop(void)
{
    uint32_t now = millis();
    light_sensor_update(now);
    temp_sensor_update(now);
    dispatch_events();
    emotion_interpreter_update(now);
    comfort_interpreter_update(now);
    light_interpreter_update(now);
    system_controller_update(now);
    buzzer_apply_intent(system_controller_get_sound_intent());
    sound_interpreter_update(now);
    buzzer_update(now);
    sound_sensor_update(now);
    eyes_update(now);
    mouth_update(now);
    armsTest();
    
    if (Serial.available())
{
    char cmd = Serial.read();

    if (cmd == 's')
        simulation_push_event(EVENT_SOUND_BURST, now);

    if (cmd == 'm')
        simulation_push_event(EVENT_SOUND_MUSIC_DETECTED, now);
     
}



}