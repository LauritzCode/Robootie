#include "eyes.h"

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>

/* Display config */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

static Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

static RoboEyes<Adafruit_SSD1306> roboEyes(display);

/* Internal state */
static EyesMode current_mode;
static ComfortFlags current_comfort;

void eyes_set_comfort_flags(ComfortFlags flags)
{
    current_comfort = flags;
}

void eyes_init(void)
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        for (;;); /* Hard stop */
    }

    roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);

    current_mode = EYES_MODE_SLEEP;
}

void eyes_set_mode(EyesMode mode)
{
    current_mode = mode;
}

void apply_base_pose(void) {
    switch(current_mode)
    {
        case EYES_MODE_SLEEP:
            roboEyes.close();
            roboEyes.setAutoblinker(OFF,3,2);
            roboEyes.setIdleMode(OFF, 2, 2);
            break;

        case EYES_MODE_AWAKE:
            roboEyes.open();
            roboEyes.setAutoblinker(ON, 3, 2);
            roboEyes.setIdleMode(ON, 2, 2);
            break;
    }
}

void apply_comfort_modifiers(void) {
    if(current_comfort.overheated) {
        roboEyes.setSweat(1);
        roboEyes.setMood(TIRED);
    } else {
        roboEyes.setSweat(0);
    }

    if(current_comfort.chilled) {
        roboEyes.setHFlicker(1);
        roboEyes.setVFlicker(1);
    } else {
        roboEyes.setHFlicker(0);
        roboEyes.setVFlicker(0); 
    }
}

void eyes_update(uint32_t now_ms) {
     (void)now_ms;

    apply_base_pose();
    apply_comfort_modifiers();

    roboEyes.update();
    }
