#pragma once 

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    EYES_BASE_SLEEP = 0,
    EYES_BASE_HALF_AWAKE,
    EYES_BASE_AWAKE
} EyesBasePose;


typedef struct {
    EyesBasePose base; 

    bool squint;
    bool sweat;
    bool tremble;

    uint8_t eye_height_L;
    uint8_t eye_height_R;
    uint8_t eye_width_L;
    uint8_t eye_width_R;
} EyesIntent;

