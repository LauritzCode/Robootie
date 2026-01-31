#include <Arduino.h>
#include "system_controller.h"
#include "brain/behavior_fsm.h"
#include "actuators/eyes.h"
#include "core/event.h"
#include "sensors/temp_sensor.h"


static TempState temp_related_type;

void system_controller_init(void)
{
    /* nothing yet */
}

void system_controller_update(uint32_t now_ms)
{
    (void)now_ms;

    /* Resolve intent (light-only, trivial version) */
    if (behavior_fsm_get_state() == BEHAVIOR_ASLEEP)
    {
        eyes_set_mode(EYES_MODE_SLEEP);
    }
    else
    {
        eyes_set_mode(EYES_MODE_AWAKE);
    }

}

void system_controller_handle_event(const Event *event)
{
    switch (event->type)
    {
        case EVENT_TEMP_ENTER_HOT:
            Serial.println("Controller: entered HOT");
            break;

        case EVENT_TEMP_EXIT_HOT:
            Serial.println("Controller: exited HOT (phew)");
            break;

        case EVENT_TEMP_ENTER_COLD:
            Serial.println("Controller: entered COLD");
            break;

        case EVENT_TEMP_EXIT_COLD:
            Serial.println("Controller: exited COLD");
            break;

        default:
            break;
    }
}
