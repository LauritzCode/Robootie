#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint32_t end_time;
    bool active;
} ActionTimer;


void timer_start(ActionTimer *t, uint32_t now_ms, uint32_t duration_ms);
bool timer_active(const ActionTimer *t, uint32_t now_ms);
void timer_stop(ActionTimer *t);

bool chance_percent(uint8_t percent);
uint8_t random_index(uint8_t count);
bool transition_true(bool current, bool *previous);
bool transition_false(bool current, bool *previous);

