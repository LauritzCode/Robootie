#include "proximity_interpreter.h"
#include "sensors/proximity_sensor.h"
#include "core/event.h"

static ProximityFlags prox_flags;


void proximity_interpreter_init(void) {
    prox_flags.too_close = false;
    prox_flags.nearby = false;
    prox_flags.clear = true;
}
void proximity_interpreter_handle_event(const Event *event) {
    switch(event->type) {
        case EVENT_PROX_TOO_CLOSE:
        prox_flags.too_close = true;
        prox_flags.nearby = false;
        prox_flags.clear = false;
        break;
        case EVENT_PROX_CLOSE: 
        prox_flags.too_close = false;
        prox_flags.nearby = true;
        prox_flags.clear = false;
        break;
        case EVENT_PROX_FAR:
        prox_flags.too_close = false;
        prox_flags.nearby = false;
        prox_flags.clear = true;
        break;
        default:
        break;
    }
}
ProximityFlags proximity_interpreter_get_flags(void) {
    return prox_flags;
}