#include "drive.h"
#include <Arduino.h>
#include "config/pins.h"

static DriveIntent current_intent = {DRIVE_STOP, 0};

// ── helpers ──────────────────────────────────────────────────────────────────

static void motor_run(uint8_t pwm, uint8_t in1, uint8_t in2, bool fwd, uint8_t speed) {
    digitalWrite(in1, fwd ? HIGH : LOW);
    digitalWrite(in2, fwd ? LOW  : HIGH);
    analogWrite(pwm, speed);
}

static void motor_brake(uint8_t pwm, uint8_t in1, uint8_t in2) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    analogWrite(pwm, 255);
}

static void motor_stop(uint8_t pwm, uint8_t in1, uint8_t in2) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(pwm, 0);
}

// apply the same command to all four motors at once
static void all_run(bool fl, bool fr, bool rl, bool rr, uint8_t speed) {
    motor_run(MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2, fl, speed);
    motor_run(MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2, fr, speed);
    motor_run(MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2, rl, speed);
    motor_run(MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2, rr, speed);
}

// ── public API ────────────────────────────────────────────────────────────────

void drive_init(void) {
    uint8_t pins[] = {
        MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2,
        MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2,
        MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2,
        MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2,
    };
    for (uint8_t i = 0; i < sizeof(pins); i++) pinMode(pins[i], OUTPUT);

    motor_stop(MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2);
    motor_stop(MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2);
    motor_stop(MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2);
    motor_stop(MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2);
}

void drive_update(uint32_t now_ms) {
    uint8_t s = current_intent.speed;
    switch (current_intent.direction) {
        case DRIVE_FORWARD:
            all_run(true, true, true, true, s);
            break;
        case DRIVE_BACKWARD:
            all_run(false, false, false, false, s);
            break;
        case DRIVE_LEFT:
            // spin left: left side back, right side forward
            motor_run(MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2, false, s);
            motor_run(MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2, false, s);
            motor_run(MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2, true,  s);
            motor_run(MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2, true,  s);
            break;
        case DRIVE_RIGHT:
            // spin right: left side forward, right side back
            motor_run(MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2, true,  s);
            motor_run(MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2, true,  s);
            motor_run(MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2, false, s);
            motor_run(MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2, false, s);
            break;
        case DRIVE_BRAKE:
            motor_brake(MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2);
            motor_brake(MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2);
            motor_brake(MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2);
            motor_brake(MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2);
            break;
        default: // DRIVE_STOP
            motor_stop(MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2);
            motor_stop(MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2);
            motor_stop(MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2);
            motor_stop(MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2);
            break;
    }
}

void drive_handle_event(const Event *event) {}

void drive_set_intent(const DriveIntent *intent) {
    current_intent = *intent;
}

void drive_test_motor(uint8_t which, uint8_t speed) {
    // stop all motors first so only the target one runs
    motor_stop(MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2);
    motor_stop(MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2);
    motor_stop(MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2);
    motor_stop(MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2);

    switch (which) {
        case 0: motor_run(MOTOR_FL_PWM, MOTOR_FL_IN1, MOTOR_FL_IN2, true, speed); Serial.println("TEST: FL (Driver1 MotorA)"); break;
        case 1: motor_run(MOTOR_FR_PWM, MOTOR_FR_IN1, MOTOR_FR_IN2, true, speed); Serial.println("TEST: FR (Driver1 MotorB)"); break;
        case 2: motor_run(MOTOR_RL_PWM, MOTOR_RL_IN1, MOTOR_RL_IN2, true, speed); Serial.println("TEST: RL (Driver2 MotorA)"); break;
        case 3: motor_run(MOTOR_RR_PWM, MOTOR_RR_IN1, MOTOR_RR_IN2, true, speed); Serial.println("TEST: RR (Driver2 MotorB)"); break;
    }

    // keep current_intent as STOP so drive_update() doesn't override the test
    current_intent = {DRIVE_STOP, 0};
}
