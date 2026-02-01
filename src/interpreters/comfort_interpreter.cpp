#include "comfort_interpreter.h"

static ComfortFlags flags;

void comfort_interpreter_init(void)
{
    flags.overheated = false;
    flags.chilled = false;
}

void comfort_interpreter_update(uint32_t now_ms)
{
    (void)now_ms;
    /* No timing logic yet */
}

void comfort_interpreter_handle_event(const Event *event)
{
    switch (event->type)
    {
        case EVENT_TEMP_ENTER_HOT:
            flags.overheated = true;
            break;

        case EVENT_TEMP_EXIT_HOT:
            flags.overheated = false;
            break;

        case EVENT_TEMP_ENTER_COLD:
            flags.chilled = true;
            break;

        case EVENT_TEMP_EXIT_COLD:
            flags.chilled = false;
            break;

        default:
            break;
    }
}

ComfortFlags comfort_interpreter_get_flags(void)
{
    return flags;
}