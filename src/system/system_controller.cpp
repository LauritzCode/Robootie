#include "system_controller.h"
#include "brain/behavior_fsm.h"
#include "actuators/eyes.h"

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