#pragma once
#include "core/event.h"
#include <stdint.h>

#define CMD_SIM_NOISE      '1'
#define CMD_SIM_BURST      '2'
#define CMD_SIM_BORED      '3'
#define CMD_SIM_MUSIC      '4'
#define CMD_SIM_TOO_CLOSE  '5'
#define CMD_SIM_NEARBY     '6'
#define CMD_SIM_FAR        '7'
#define CMD_SIM_TALKING    '8'

#define CMD_DRIVE_FORWARD    'f'
#define CMD_DRIVE_BACKWARD   'b'
#define CMD_DRIVE_LEFT       'l'
#define CMD_DRIVE_RIGHT      'r'
#define CMD_DRIVE_STOP       's'
#define CMD_DRIVE_BRAKE      'k'
#define CMD_DRIVE_SPEED_UP   'u'
#define CMD_DRIVE_SPEED_DOWN 'd'

// Motor isolation test — one motor at a time, PWM 180, stop with 's'
#define CMD_TEST_FL  'A'   // Driver1 MotorA (code: front-left)
#define CMD_TEST_FR  'B'   // Driver1 MotorB (code: front-right)
#define CMD_TEST_RL  'C'   // Driver2 MotorA (code: rear-left)
#define CMD_TEST_RR  'D'   // Driver2 MotorB (code: rear-right)

void bluetooth_init(void);
void bluetooth_update(uint32_t now_ms);
