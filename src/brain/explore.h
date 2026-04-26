#pragma once
#include <stdint.h>
#include "core/event.h"
#include "actuators/sound_intent.h"

void explore_init(void);
void explore_start(uint32_t now_ms);
void explore_quit(void);
void explore_update(uint32_t now_ms);
void explore_handle_event(const Event *event);
const SoundIntent* explore_get_sound_intent(void);
bool explore_is_silly(void);
bool explore_is_scanning(void);
bool explore_is_greeting(void);
bool explore_is_waving(void);
bool explore_is_trapped(void);
