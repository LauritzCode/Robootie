#include <Arduino.h>
#include "arms.h"
#include "config/pins.h"
#include <Servo.h>

Servo leftArm;
Servo rightArm;

ArmsPose curr_pose;
ArmsPose prev_pose;
ArmsIntent arms_intent;

uint32_t wave_last_move_time = 0;
uint32_t gof_last_move_time = 0;
uint32_t dance_last_move_time = 0;
uint32_t attack_last_move_time = 0;

static bool pose = false;

void arms_init(void) {
    leftArm.attach(LEFT_ARM);
    rightArm.attach(RIGHT_ARM);
    curr_pose = ARMS_IDLE;
}

static void arms_idle() {
    leftArm.write(90);
    rightArm.write(90);
}

static void arms_wave(uint32_t now_ms) {

    if(now_ms - wave_last_move_time >= 500) {
        if(pose) {
            leftArm.write(90);
            rightArm.write(90);
        } else {
            leftArm.write(0);
            rightArm.write(0); 
        }
         wave_last_move_time = now_ms;
         pose = !pose;
    }
}

static void arms_gof(uint32_t now_ms) {
    
}

static void arms_dance(uint32_t now_ms) {
    
}
static void arms_attack(uint32_t now_ms) {
    
}


void arms_update(uint32_t now_ms) {
    switch(arms_intent.pose) {
        case ARMS_IDLE:
        arms_idle();
        break;
        case ARMS_WAVE:
        arms_wave(now_ms);
        break;
        case ARMS_GOF_OUT:
        arms_gof(now_ms);
        break;
        case ARMS_DANCE:
        arms_dance(now_ms);
        break;
        case ARMS_ATTACK:
        arms_attack(now_ms);
        break;
        default: 
        arms_idle(); 
        break;
    }
}
void arms_handle_event(const Event *event) {

}
void arms_set_intent(const ArmsIntent *intent) {
    arms_intent = *intent;
}
