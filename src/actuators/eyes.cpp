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

/* Internal state */
static EyesMode current_mode;
static ComfortFlags current_temp_comfort;
static LightFlags current_light_comfort;


void eyes_set_temp_comfort_flags(ComfortFlags flags)
{
    current_temp_comfort = flags;
}

void eyes_set_light_comfort_flags(LightFlags flags)
{
    current_light_comfort = flags;
}

void eyes_init(void)
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        for (;;); /* Hard stop */
    }

    roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
    eyes_apply_defaults();

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

    /* NOTE:
 * Temporary stacked modifier logic.
 * Will be replaced by EyesIntent resolver
 * once audio/microphone is added.
 */

 /*
    if (current_mode == EYES_MODE_SLEEP)
    {
        if (current_light_comfort.semi_bright)
        {
            Serial.println("Ah? Is bright?");
        }
    }

    if (current_mode == EYES_MODE_AWAKE) {
        if(current_light_comfort.too_bright) {
            Serial.println("Ahhh, too bright!");
            roboEyes.setHeight((byte)SQUINT, (byte)SQUINT);
        }
    }


    if (current_temp_comfort.overheated)
    {
        roboEyes.setSweat(1);
        // roboEyes.setMood(TIRED); // TIRED FOR NOW, LATER WILL BE APPLIED AS MOOD
    }
    else if (current_temp_comfort.hot)
    {
        roboEyes.setSweat(1);   
    }
    else
    {
        roboEyes.setSweat(0);
    }


   if (current_temp_comfort.chilled)
    {
        roboEyes.setHFlicker(1);
    }
    else if (current_temp_comfort.cold)
    {
        roboEyes.setHFlicker(1);
    }
    else
    {
        roboEyes.setHFlicker(0);
    }
        */
}

void eyes_update(uint32_t now_ms) {
     (void)now_ms;

     eyes_apply_defaults();

     if (current_mode == EYES_MODE_SLEEP &&
        current_light_comfort.semi_bright)
    {
        // override base pose entirely
        roboEyes.open(1, 0);
        roboEyes.setIdleMode(OFF, 2, 2);
        roboEyes.setAutoblinker(OFF, 3, 2);
    }
    else
    {
        apply_base_pose();
    }
    apply_comfort_modifiers();
    roboEyes.update();
    }


    static void eyes_apply_defaults(void)
{
    // Geometry
    roboEyes.setHeight(base_eye_height_L, base_eye_height_R);
    roboEyes.setWidth(base_eye_width_L, base_eye_width_R);

    // Effects
    roboEyes.setSweat(0);
    roboEyes.setHFlicker(0);
    roboEyes.setVFlicker(0);

    // Borders / extras (only if you touched them elsewhere)
    // roboEyes.setBorder(0);

    // Mood reset will come later (emotion system)

    roboEyes.setMood(EYES_MOOD_NEUTRAL);
}