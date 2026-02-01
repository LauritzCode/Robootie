#include <Arduino.h>
#include "system_controller.h"
#include "brain/behavior_fsm.h"
#include "actuators/eyes.h"
#include "core/event.h"
#include "interpreters/comfort_interpreter.h"
#include "sensors/temp_sensor.h"



static TempState temp_related_type;
static ComfortState current_comfort = COMFORT_COMFY;
static SystemIntent intent;

void system_controller_init(void)
{
    /* nothing yet */
}

void system_controller_update(uint32_t now_ms)
{
    (void)now_ms;

    ComfortFlags comfort = comfort_interpreter_get_flags();
    eyes_set_comfort_flags(comfort);

   EyesMode mode;

/* Resolve intent */
    if (comfort.overheated)
    {
        mode = EYES_MODE_AWAKE;
    }
    else if (behavior_fsm_get_state() == BEHAVIOR_ASLEEP)
    {
        mode = EYES_MODE_SLEEP;
    } else
    {
        mode = EYES_MODE_AWAKE;
    }

    eyes_set_mode(mode);

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
