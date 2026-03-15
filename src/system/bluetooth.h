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

#define CMD_DRIVE_FORWARD   'f'
#define CMD_DRIVE_BACKWARD  'b'
#define CMD_DRIVE_STOP      's'
#define CMD_DRIVE_BRAKE     'k'
#define CMD_DRIVE_SPEED_UP  'u'

void bluetooth_init(void);
void bluetooth_update(uint32_t now_ms);
