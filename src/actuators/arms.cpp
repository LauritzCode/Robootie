#include <Arduino.h>
#include "arms.h"
#include "config/pins.h"
#include <Servo.h>
#include "core/timebase.h"

Servo leftArm;
Servo rightArm;

ArmsPose curr_pose;
ArmsPose prev_pose;
ArmsIntent arms_intent;
ActionTimer arms_transient_timer;
uint32_t wave_last_move_time = 0;
uint32_t shiver_last_move_time = 0;
uint32_t hot_last_move_time = 0;
uint32_t gof_last_move_time = 0;
uint32_t dance_last_move_time = 0;
uint32_t attack_last_move_time = 0;
uint32_t attack_polarity_time = 0;
uint32_t next_dance_move_ms = 0;
uint32_t next_attack_move_ms = 0;
bool wave_pose = false;
bool gof_pose = false;
bool attack_pose = false;
bool attack_pol = false;
bool hot_pose = false;
bool shiver_pose = false;

void arms_init(void) {
    randomSeed(analogRead(0));
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
        if(wave_pose) {
            leftArm.write(0);
            rightArm.write(90);
        } else {
            leftArm.write(0);
            rightArm.write(0); 
        }
         wave_last_move_time = now_ms;
         wave_pose = !wave_pose;
    }
}

static void arms_hot(uint32_t now_ms) {

    if(now_ms - hot_last_move_time >= 200) {
        if(hot_pose) {
            leftArm.write(0);
            rightArm.write(90);
        } else {
            leftArm.write(0);
            rightArm.write(0); 
        }
         hot_last_move_time = now_ms;
         hot_pose = !hot_pose;
    }
}

static void arms_shiver(uint32_t now_ms) {

    if(now_ms - shiver_last_move_time >= 200) {
        if(shiver_pose) {
            leftArm.write(90);
            rightArm.write(90);
        } else {
            leftArm.write(110);
            rightArm.write(110); 
        }
         shiver_last_move_time = now_ms;
         shiver_pose = !shiver_pose;
    }
}

static void arms_gof(uint32_t now_ms) {

        if(now_ms - gof_last_move_time >= 200) {
        if(gof_pose) {
            leftArm.write(90);
            rightArm.write(0);
        } else {
            leftArm.write(0);
            rightArm.write(90); 
        }
         gof_last_move_time = now_ms;
         gof_pose = !gof_pose;
    }
    
}

static void arms_dance(uint32_t now_ms) {

    
    if(now_ms - dance_last_move_time >= next_dance_move_ms) {
         leftArm.write(random(0, 90));
         rightArm.write(random(0, 90));
         dance_last_move_time = now_ms;
         next_dance_move_ms = random(400,2000);
    }
    
}
static void arms_attack(uint32_t now_ms) {
    
    if(now_ms - attack_last_move_time >= next_attack_move_ms) {
       attack_last_move_time = now_ms;
       next_attack_move_ms = random(100, 500);
       attack_pose = !attack_pose;
       if(now_ms - attack_polarity_time >= 1500) {
        attack_pol = !attack_pol;
        attack_polarity_time = now_ms;

       }

       if(attack_pol) {
        leftArm.write(0); 
       if(attack_pose) {
       rightArm.write(90); 
       } else {
       rightArm.write(0); 
       }
       } else {
        rightArm.write(0); 
       if(attack_pose) {
       leftArm.write(90); 
       } else {
       leftArm.write(0); 
       }
       }

    }
}


void arms_update(uint32_t now_ms) {

    if (timer_active(&arms_transient_timer, now_ms) == false && 
    arms_intent.one_shot) {
    arms_intent.pose = ARMS_IDLE;
}
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
        case ARMS_HOT:
        arms_hot(now_ms);
        break;
        case ARMS_SHIVER:
        arms_shiver(now_ms);
        break;
        default: 
        arms_idle(); 
        break;
    }
}
void arms_handle_event(const Event *event) {
        switch (event->type)
    {
        case EVENT_SOUND_BURST:
            arms_intent.pose = ARMS_GOF_OUT;
            timer_start(&arms_transient_timer, event->timestamp_ms, 1000);
            break;
        case EVENT_SOUND_TALKING:
            arms_intent.pose = ARMS_GOF_OUT;
            timer_start(&arms_transient_timer, event->timestamp_ms, 1000);
            break;
        case EVENT_SOUND_MUSIC_DETECTED:
            arms_intent.pose = ARMS_DANCE;
            break;
        case EVENT_SOUND_GENERAL_NOISE:
            arms_intent.pose = ARMS_ATTACK;
            timer_start(&arms_transient_timer, event->timestamp_ms, 3000);
            break;
        default:
            arms_intent.pose = ARMS_IDLE;
            break;
    }
}

void arms_set_intent(const ArmsIntent *intent) {
    arms_intent = *intent;
}
