#pragma once 

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    EYES_BASE_SLEEP = 0,
    EYES_BASE_HALF_AWAKE,
    EYES_BASE_AWAKE
} EyesBasePose;

typedef enum {
    EYES_MOOD_NONE = 0,   // means "don't touch mood"
    EYES_MOOD_SAD,
    EYES_MOOD_TIRED,
    EYES_MOOD_HAPPY,
    EYES_MOOD_ANGRY
} EyesMood;


typedef struct {
    EyesBasePose base; 

    bool squint;
    bool sweat;
    bool tremble;
    bool override_eye_height;
    bool override_mood;
    EyesMood mood;

    uint8_t eye_height_L;
    uint8_t eye_height_R;
    uint8_t eye_width_L;
    uint8_t eye_width_R;
} EyesIntent;

