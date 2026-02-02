#include <Arduino.h>
#include "system_controller.h"
#include "brain/behavior_fsm.h"
#include "actuators/eyes.h"
#include "core/event.h"
#include "config/thresholds.h"
#include "interpreters/comfort_interpreter.h"
#include "interpreters/light_interpreter.h"
#include "sensors/light_sensor.h"
#include "sensors/temp_sensor.h"
#include "actuators/eyes_intent.h"
#include "interpreters/emotion_interpreter.h"


static ComfortState current_comfort;

void system_controller_init(void)
{
    /* nothing yet */
}

void system_controller_update(uint32_t now_ms)
{
    (void)now_ms;
    EyesIntent intent = {0};

    /* base geometry */
    intent.eye_height_L = EYE_BASE_HEIGHT;
    intent.eye_height_R = EYE_BASE_HEIGHT;
    intent.eye_width_L  = EYE_BASE_WIDTH;
    intent.eye_width_R  = EYE_BASE_WIDTH;

    

    ComfortFlags comfort = comfort_interpreter_get_flags();
    LightFlags light = light_interpreter_get_flags();
    EmotionState emo = emotion_interpreter_get_state();


    // Resolve emotions
    if (emo.transient == TRANSIENT_STARTLED)
{
    intent.base = EYES_BASE_AWAKE;
    intent.tremble = true;
    intent.eye_height_L = EYE_BASE_HEIGHT - 6;
    intent.eye_height_R = EYE_BASE_HEIGHT - 6;

    eyes_set_intent(&intent);
    return;   
}

   if (emo.base == EMOTION_TIRED)
    intent.eye_height_L = intent.eye_height_R = EYE_BASE_HEIGHT - 4;

   if (emo.base == EMOTION_SAD)
    intent.eye_height_L = intent.eye_height_R = EYE_BASE_HEIGHT - 6;



// Resolve intent 
    if (comfort.overheated)
    {
        intent.base = EYES_BASE_AWAKE;
    }
    else if (behavior_fsm_get_state() == BEHAVIOR_ASLEEP) {
         if (light.semi_bright) {
        intent.base = EYES_BASE_HALF_AWAKE;
         } else
        intent.base = EYES_BASE_SLEEP;
    } else
    {
        intent.base = EYES_BASE_AWAKE;
    }

    
/* Modifiers */
    intent.sweat = comfort.hot || comfort.overheated;
    intent.tremble = comfort.cold || comfort.chilled;

    if (light.too_bright)
    {
        intent.squint = true;
        intent.eye_height_L = SQUINT;
        intent.eye_height_R = SQUINT;
    }

    eyes_set_intent(&intent);

}

void system_controller_handle_event(const Event *event)
{
    switch (event->type)
    {
        case EVENT_TEMP_ENTER_HOT:
            current_comfort = COMFORT_HOT;
            Serial.println("Controller: entered HOT");
            break;

        case EVENT_TEMP_EXIT_HOT:
            Serial.println("Controller: exited HOT (phew)");
            break;

        case EVENT_TEMP_ENTER_COMFY:
            Serial.println("Is comfy.");
            current_comfort = COMFORT_COMFY;
            break;

        case EVENT_TEMP_ENTER_COLD:
            current_comfort = COMFORT_COLD;
            Serial.println("Controller: entered COLD");
            
            break;

        case EVENT_TEMP_EXIT_COLD:
            Serial.println("Controller: exited COLD");
            break;

        default:
            break;
    }
}
