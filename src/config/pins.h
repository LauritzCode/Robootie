#pragma once 

#define LIGHT_SENSOR_PIN 1
#define TEMP_SENSOR_PIN 5
#define PIN_BUZZER 3
#define AUDIO_DIGITAL_PIN 5
#define AUDIO_ANALOG_PIN 4
#define LEFT_ARM 8
#define RIGHT_ARM 9


// motors — TB6612FNG, STBY tied to 5V on both drivers

// Driver 1 — front wheels
#define MOTOR_FL_PWM   4    // PWMA
#define MOTOR_FL_IN1   25   // swapped: motor wired with reversed polarity
#define MOTOR_FL_IN2   23
#define MOTOR_FR_PWM   5    // PWMB
#define MOTOR_FR_IN1   29   // BIN1
#define MOTOR_FR_IN2   31   // BIN2

// Driver 2 — rear wheels
#define MOTOR_RL_PWM   6    // PWMA
#define MOTOR_RL_IN1   33   // AIN1
#define MOTOR_RL_IN2   35   // AIN2
#define MOTOR_RR_PWM   7    // PWMB
#define MOTOR_RR_IN1   39   // BIN1
#define MOTOR_RR_IN2   41   // BIN2

