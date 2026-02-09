#include "timebase.h"

void timer_start(ActionTimer *t, uint32_t now_ms, uint32_t duration_ms)
{
    t->end_time = now_ms + duration_ms;
    t->active = true;
}

bool timer_active(const ActionTimer *t, uint32_t now_ms)
{
    if (!t->active)
        return false;

    if (now_ms >= t->end_time)
        return false;

    return true;
}

void timer_stop(ActionTimer *t)
{
    t->active = false;
}


bool chance_percent(uint8_t percent)
{
    return (random(100) < percent);
}

uint8_t random_index(uint8_t count)
{
    if (count == 0)
        return 0;

    return random(count);
}

bool transition_true(bool current, bool *previous)
{
    bool triggered = (current && !(*previous));
    *previous = current;
    return triggered;
}

bool transition_false(bool current, bool *previous)
{
    bool triggered = (!current && (*previous));
    *previous = current;
    return triggered;
}
