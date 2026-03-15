#include "bluetooth.h"
#include "brain/behavior_fsm.h"
#include <Arduino.h>
#include "core/event_queue.h"
#include "actuators/drive.h"


static uint8_t current_speed = 0;

void bluetooth_init(void) {
    Serial1.begin(9600);
}

static void bluetooth_drive(DriveDirection direction, uint8_t speed) {
    DriveIntent intent = {direction, speed};
    drive_set_intent(&intent);
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

        case CMD_DRIVE_FORWARD:
    bluetooth_drive(DRIVE_FORWARD, current_speed);
    break;
    case CMD_DRIVE_BACKWARD:
        bluetooth_drive(DRIVE_BACKWARD, current_speed);
        break;
    case CMD_DRIVE_STOP:
        current_speed = 0;
        bluetooth_drive(DRIVE_STOP, 0);
        break;
    case CMD_DRIVE_BRAKE:
        bluetooth_drive(DRIVE_BRAKE, 255);
        break;
    case CMD_DRIVE_SPEED_UP:
        if (current_speed <= 245) current_speed += 10;
        bluetooth_drive(DRIVE_FORWARD, current_speed);
        Serial.print("Speed: ");
        Serial.println(current_speed);
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
