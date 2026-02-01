
#include <Arduino.h>
#include "light_interpreter.h"
#include "config/thresholds.h"

LightFlags current_light_level;

void light_interpreter_init(void) {

    current_light_level.dark = false;
    current_light_level.semi_bright = false;
    current_light_level.bright = false;
    current_light_level.too_bright = false;
}
void light_interpreter_update(uint32_t now_ms) {
    // no timing based events yet. 
}

void light_interpreter_handle_event(const Event *event)
{
    switch (event->type)
    {
        case EVENT_LIGHT_BECAME_DARK:
            current_light_level.dark = true;
            current_light_level.semi_bright = false;
            current_light_level.bright = false;
            current_light_level.too_bright = false;
            break;

        case EVENT_LIGHT_BECAME_SEMI_BRIGHT:
            current_light_level.dark = false;
            current_light_level.semi_bright = true;
            current_light_level.bright = false;
            current_light_level.too_bright = false;
            break;

        case EVENT_LIGHT_BECAME_BRIGHT:
            current_light_level.dark = false;
            current_light_level.semi_bright = false;
            current_light_level.bright = true;
            current_light_level.too_bright = false;
            break;

        case EVENT_LIGHT_BECAME_TOO_BRIGHT:
            current_light_level.dark = false;
            current_light_level.semi_bright = false;
            current_light_level.bright = false;
            current_light_level.too_bright = true;
            break;

        default:
            break;
    }
}


LightFlags light_interpreter_get_flags(void) {
    return current_light_level;
}


