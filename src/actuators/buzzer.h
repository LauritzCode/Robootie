#pragma once

#include <stdint.h>
#include "actuators/sound_intent.h"

void buzzer_apply_intent(const SoundIntent* intent);
void buzzer_update(uint32_t now_ms);
bool buzzer_is_busy(void);
