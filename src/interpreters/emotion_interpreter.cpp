#include "emotion_interpreter.h"
#include "interpreters/comfort_interpreter.h"
#include <Arduino.h>

static EmotionState current_emotion;
static ComfortFlags current_comfort;

// timers for transient emotions 
static uint32_t transient_end_time = 0;

void emotion_interpreter_init(void)
{
    current_emotion.base = EMOTION_NEUTRAL;
    current_emotion.transient = TRANSIENT_NONE;
}

void emotion_interpreter_handle_event(const Event *event)
{
    switch (event->type)
    {
        case EVENT_TEMP_ENTER_HOT:
            current_emotion.base = EMOTION_TIRED;
            break;

        case EVENT_TEMP_EXIT_HOT:
            current_emotion.base = EMOTION_NEUTRAL;
            break;

        case EVENT_SOUND_BURST:
            current_emotion.transient = TRANSIENT_STARTLED;
            transient_end_time = event->timestamp_ms + 3000;
            break;

        case EVENT_SOUND_MUSIC_DETECTED:
            current_emotion.transient = TRANSIENT_MUSIC;
            transient_end_time = event->timestamp_ms + 5500;
            break;

        default:
            break;
    }
}

void emotion_interpreter_update(uint32_t now_ms)
{
    current_comfort = comfort_interpreter_get_flags();
    

    if (current_emotion.transient != TRANSIENT_NONE &&
        now_ms >= transient_end_time)
    {
        current_emotion.transient = TRANSIENT_NONE;
    }

    if(current_comfort.overheated || current_comfort.chilled) {
        Serial.println("Emotion detected: overheated or chilled");
        current_emotion.base = EMOTION_SAD;
    }  else
    {
        current_emotion.base = EMOTION_NEUTRAL;
    }

}

EmotionState emotion_interpreter_get_state(void)
{
    return current_emotion;
}