#include <Arduino.h>
#include <Wire.h>

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
#include "sensors/proximity_sensor.h"
#include "interpreters/proximity_interpreter.h"
#include "system/bluetooth.h"
#include "actuators/drive.h"
#include "sensors/mpu6050.h"



void setup(void)
{
    drive_init();  // must be first — STBY is tied to 5V so driver is live on power-on;
                   // floating IN pins cause random motor movement until we drive them LOW

    Serial.begin(9600);

    event_queue_init();
    behavior_fsm_init();
    light_sensor_init();
    // temp_sensor_init();       // DISABLED: temp sensor readings unreliable on hardware
    sound_sensor_init();
    system_controller_init();
    light_interpreter_init();
    // comfort_interpreter_init(); // DISABLED: temp sensor readings unreliable on hardware
    proximity_interpreter_init();
    eyes_init();
    mouth_init();
    arms_init();
    proximity_init();
    bluetooth_init();
    motion_sensor_init();
    Wire.setWireTimeout(3000, true);  // 3ms I2C timeout; resets bus on hang from motor noise
}

void loop(void)
{
    uint32_t now = millis();
    light_sensor_update(now);
    // temp_sensor_update(now);       // DISABLED: temp sensor readings unreliable on hardware
    dispatch_events();
    emotion_interpreter_update(now);
    // comfort_interpreter_update(now); // DISABLED: temp sensor readings unreliable on hardware
    light_interpreter_update(now);
    system_controller_update(now);
    // buzzer_apply_intent(system_controller_get_sound_intent()); // DISABLED: silenced for testing
    sound_interpreter_update(now);
    // buzzer_update(now); // DISABLED: silenced for testing
   // sound_sensor_update(now);
    eyes_update(now);
    mouth_update(now);
    arms_update(now);
    proximity_update(now);
    bluetooth_update(now);
    drive_update(now);
    motion_sensor_update(now);
}