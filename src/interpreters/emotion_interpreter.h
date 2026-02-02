#pragma once 

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "core/event.h"
#include "brain/behavior_fsm.h"

typedef enum {
    EMOTION_NEUTRAL = 0,
    EMOTION_HAPPY,
    EMOTION_SAD,
    EMOTION_ANGRY,
    EMOTION_TIRED
} BaseEmotion;

typedef enum {
    TRANSIENT_NONE = 0,
    TRANSIENT_STARTLED,
    TRANSIENT_LAUGHING
} TransientEmotion;

typedef struct {
    BaseEmotion base;
    TransientEmotion transient;
} EmotionState;

void emotion_interpreter_init(void);
void emotion_interpreter_update(uint32_t now_ms);
void emotion_interpreter_handle_event(const Event *event);

EmotionState emotion_interpreter_get_state(void);
