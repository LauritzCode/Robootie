#include "drive.h"
#include <Arduino.h>
#include "config/pins.h"

static DriveIntent current_intent = {DRIVE_STOP, 0};

void drive_init(void) {
    pinMode(MOTOR_A_PWM, OUTPUT);
    pinMode(MOTOR_A_IN1, OUTPUT);
    pinMode(MOTOR_A_IN2, OUTPUT);

    analogWrite(MOTOR_A_PWM, 0);
}
void drive_update(uint32_t now_ms) {
    switch(current_intent.direction) {
        case DRIVE_FORWARD:
        digitalWrite(MOTOR_A_IN1, HIGH);
        digitalWrite(MOTOR_A_IN2, LOW);
        analogWrite(MOTOR_A_PWM, current_intent.speed);
        break;
        case DRIVE_BACKWARD:
        digitalWrite(MOTOR_A_IN1, LOW);
        digitalWrite(MOTOR_A_IN2, HIGH);
        analogWrite(MOTOR_A_PWM, current_intent.speed);
        break;
        case DRIVE_BRAKE:
        digitalWrite(MOTOR_A_IN1, HIGH);
        digitalWrite(MOTOR_A_IN2, HIGH);
        analogWrite(MOTOR_A_PWM, 255);
        break;
        default:
        digitalWrite(MOTOR_A_IN1, LOW);
        digitalWrite(MOTOR_A_IN2, LOW);
        analogWrite(MOTOR_A_PWM, 0);
        break;
    }
}
void drive_handle_event(const Event *event) {

}
void drive_set_intent(const DriveIntent *intent) {
    current_intent = *intent;
}

