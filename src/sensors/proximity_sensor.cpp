#include "proximity_sensor.h"
#include "core/event.h"
#include "core/event_queue.h"
#include "Adafruit_VL53L0X.h"
#include "brain/behavior_context.h"
#include "brain/behavior_fsm.h"
#include "system/system_controller.h"
#include "config/thresholds.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

static ProximityState proximity_state = PROXIMITY_FAR;
static uint32_t last_read_time = 0;
static uint32_t last_transition_time = 0;

void proximity_init(void) {
    if (!lox.begin()) {
        Serial.println("VL53L0X init failed!");
        return;
    }
    lox.startRangeContinuous();
    Serial.println("VL53L0X ready.");
}

void proximity_update(uint32_t now_ms) {

    BehaviorState behavior_state = behavior_fsm_get_state();
    BehaviorContext behavior_context = system_controller_get_context();

    if (behavior_state == BEHAVIOR_ASLEEP) return;

    uint32_t interval = 1000;
    if (behavior_context == CONTEXT_LISTENING || proximity_state == PROXIMITY_NEARBY || proximity_state == PROXIMITY_TOO_CLOSE)
        interval = 200;

    if (now_ms - last_read_time < interval) return;
    last_read_time = now_ms;

    uint16_t distance = lox.readRange();

    // determine new state first
    ProximityState new_state;
    if (distance < PROX_TOO_CLOSE)
        new_state = PROXIMITY_TOO_CLOSE;
    else if (distance < PROX_CLOSE)
        new_state = PROXIMITY_NEARBY;
    else
        new_state = PROXIMITY_FAR;

    // only fire event on transition
    if (new_state != proximity_state) {
    if (now_ms - last_transition_time >= 2000) {
        last_transition_time = now_ms;
        proximity_state = new_state;

        Event e;
        e.timestamp_ms = now_ms;
        e.value = distance;

        if (new_state == PROXIMITY_TOO_CLOSE) {
            e.type = EVENT_PROX_TOO_CLOSE;
        } else if (new_state == PROXIMITY_NEARBY) {
            e.type = EVENT_PROX_CLOSE;
        } else {
            e.type = EVENT_PROX_FAR;
        }

        event_queue_push(e);
    }
}
}