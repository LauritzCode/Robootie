#include "bluetooth.h"
#include "brain/behavior_fsm.h"
#include <Arduino.h>
#include "core/event_queue.h"

void bluetooth_init(void) {
    Serial1.begin(9600);
}

static void bluetooth_push_event(EventType type, uint32_t now_ms)  {
     Event e = {};
    e.type = type;
    e.timestamp_ms = now_ms;

    event_queue_push(e);
    Serial.println("Event now pushed by bluetooth");
}

static void bluetooth_handle_cmd(unsigned char cmd, uint32_t now_ms) {

    switch(cmd) {
        case CMD_SIM_NOISE: 
        bluetooth_push_event(EVENT_SOUND_GENERAL_NOISE, now_ms);
        break;
        case CMD_SIM_BURST: 
        bluetooth_push_event(EVENT_SOUND_BURST, now_ms);
        break;
        case CMD_SIM_BORED: 
        behavior_fsm_set_state(BEHAVIOR_BORED);
        break;
        case CMD_SIM_MUSIC: 
        bluetooth_push_event(EVENT_SOUND_MUSIC_DETECTED, now_ms);
        break;
        case CMD_SIM_TOO_CLOSE: 
        bluetooth_push_event(EVENT_PROX_TOO_CLOSE, now_ms);
        break;
        case CMD_SIM_NEARBY: 
        bluetooth_push_event(EVENT_PROX_CLOSE, now_ms);
        break;
        case CMD_SIM_FAR: 
        bluetooth_push_event(EVENT_PROX_FAR, now_ms);
        break;
        case CMD_SIM_TALKING: 
        bluetooth_push_event(EVENT_SOUND_TALKING, now_ms);
        break;
        default:
        break;
    }
}

void bluetooth_update(uint32_t now_ms) {
    if (Serial1.available()) {
        unsigned char cmd = Serial1.read();
        bluetooth_handle_cmd(cmd, now_ms);
    }
}
