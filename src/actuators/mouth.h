#pragma once

#include <Arduino.h>
#include "core/event.h"

typedef struct
{
    bool response;
    bool shy_response;
    bool quiet;
} SpeechFlags;

void mouth_init();

void mouth_express(char *expression);

void mouth_update(uint32_t now_ms);

void mouth_clear();

void mouth_handle_event(const Event *event);

SpeechFlags speech_get_flags(void);