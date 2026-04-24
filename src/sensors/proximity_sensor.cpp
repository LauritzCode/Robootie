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
static uint32_t last_read_time    = 0;
static uint32_t confirm_near_ms   = 0;  // when we first started seeing close readings
static uint32_t confirm_far_ms    = 0;  // when we first started seeing empty readings
static bool proximity_initialized = false;

static const uint32_t READ_INTERVAL_MS  = 200;
static const uint32_t NEAR_CONFIRM_MS   = 500;   // hold close for this long to confirm arrival
static const uint32_t FAR_CONFIRM_MS    = 3000;  // hold empty for this long to confirm departure

void proximity_init(void) {
    for (uint8_t attempt = 1; attempt <= 5; attempt++) {
        delay(300);
        Serial.print("VL53L0X init attempt "); Serial.print(attempt); Serial.println("/5...");
        if (lox.begin()) {
            lox.startRangeContinuous();
            proximity_initialized = true;
            Serial.println("VL53L0X ready.");
            return;
        }
        Serial.println("  no response, retrying...");
    }
    Serial.println("VL53L0X init failed after 5 attempts.");
}

void proximity_update(uint32_t now_ms) {

    if (!proximity_initialized) return;
    if (behavior_fsm_get_state() == BEHAVIOR_ASLEEP) return;

    if (now_ms - last_read_time < READ_INTERVAL_MS) return;
    last_read_time = now_ms;

    uint16_t distance = lox.readRange();
    Serial.print("[PROX] "); Serial.print(distance); Serial.println("mm");

    if (proximity_state == PROXIMITY_FAR) {
        // Waiting for someone to arrive — need NEAR_CONFIRM_MS of close readings
        if (distance < PROX_CLOSE) {
            if (confirm_near_ms == 0) confirm_near_ms = now_ms;
            if (now_ms - confirm_near_ms >= NEAR_CONFIRM_MS) {
                proximity_state = PROXIMITY_NEARBY;
                confirm_near_ms = 0;
                Event e = { EVENT_PROX_CLOSE, now_ms, distance };
                event_queue_push(e);
            }
        } else {
            confirm_near_ms = 0;
        }

    } else { // PROXIMITY_NEARBY
        // Waiting for them to leave — need FAR_CONFIRM_MS of empty readings
        if (distance > PROX_NEARBY_EXIT) {
            if (confirm_far_ms == 0) confirm_far_ms = now_ms;
            if (now_ms - confirm_far_ms >= FAR_CONFIRM_MS) {
                proximity_state = PROXIMITY_FAR;
                confirm_far_ms = 0;
                Event e = { EVENT_PROX_FAR, now_ms, distance };
                event_queue_push(e);
            }
        } else {
            confirm_far_ms = 0;
        }
    }
}