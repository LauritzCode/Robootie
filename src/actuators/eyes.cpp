#include "eyes.h"

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>

/* Display config */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define EYES_MOOD_NEUTRAL 0

static EyesIntent current_intent;
static byte base_eye_height_L = 36;
static byte base_eye_height_R = 36;
static byte base_eye_width_L = 36;
static byte base_eye_width_R = 36;

static void eyes_apply_defaults(void);

static Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

static RoboEyes<Adafruit_SSD1306> roboEyes(display);

void eyes_set_intent(const EyesIntent *intent)
{
    current_intent = *intent;
}

void eyes_init(void)
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        for (;;); /* Hard stop */
    }

    roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
    eyes_apply_defaults();
}

void eyes_update(uint32_t now_ms) {
     (void)now_ms;

    switch(current_intent.base) {
        case EYES_BASE_SLEEP:
        apply_base_sleep();
        break;
        case EYES_BASE_HALF_AWAKE:
        apply_base_half_awake();
        break;
        case EYES_BASE_AWAKE:
        default: 
        apply_base_awake();
        break;
    }


    // Modifiers
    if (current_intent.sweat)
        roboEyes.setSweat(1);

    if (current_intent.tremble)
        roboEyes.setHFlicker(1);

    if (current_intent.override_eye_height)
        roboEyes.setHeight(current_intent.eye_height_L,
                           current_intent.eye_height_R);

    if(current_intent.override_mood) {
        switch(current_intent.mood) {
            case EYES_MOOD_SAD:
            roboEyes.setMood(TIRED);
            break;
            case EYES_MOOD_TIRED:
            roboEyes.setMood(TIRED);
            break;
        }
    }
    


    roboEyes.update();
    }


    static void eyes_apply_defaults(void) {

    // Effects
    roboEyes.setSweat(0);
    roboEyes.setHFlicker(0);
    roboEyes.setVFlicker(0);
    roboEyes.setMood(EYES_MOOD_NEUTRAL);
}

void apply_base_sleep() {

    eyes_apply_defaults();
        // Geometry
     roboEyes.setHeight(base_eye_height_L, base_eye_height_R);
     roboEyes.setWidth(base_eye_width_L, base_eye_width_R);
    
    roboEyes.close();
    roboEyes.setIdleMode(OFF, 2, 2);
    roboEyes.setAutoblinker(OFF, 3, 2);
}

void apply_base_awake() {

    eyes_apply_defaults();
        // Geometry
     roboEyes.setHeight(base_eye_height_L, base_eye_height_R);
     roboEyes.setWidth(base_eye_width_L, base_eye_width_R);
    
    roboEyes.open();
    roboEyes.setIdleMode(ON, 2, 2);
    roboEyes.setAutoblinker(ON, 3, 2);
}

void apply_base_half_awake() {
    eyes_apply_defaults();
    roboEyes.open(1, 0);
    roboEyes.setIdleMode(OFF, 2, 2);
    roboEyes.setAutoblinker(OFF, 3, 2);
}



