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

void eyes_update(uint32_t now_ms) {
    (void)now_ms;

    switch(current_mode) {
        case EYES_MODE_SLEEP:
        roboEyes.close();
        roboEyes.setAutoblinker(OFF, 3, 2);
        roboEyes.setIdleMode(OFF, 2, 2);
        break;

        case EYES_MODE_AWAKE:
            roboEyes.open();
            roboEyes.setAutoblinker(ON, 3, 2);
            roboEyes.setIdleMode(ON, 2, 2);
            break;

        default:
            break;
    }

    roboEyes.update();
    }
