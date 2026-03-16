#include <Arduino.h>
#include "system_controller.h"
#include "brain/behavior_fsm.h"
#include "actuators/eyes.h"
#include "core/event.h"
#include "config/thresholds.h"
#include "interpreters/comfort_interpreter.h"
#include "interpreters/light_interpreter.h"
#include "sensors/light_sensor.h"
#include "sensors/temp_sensor.h"
#include "actuators/eyes_intent.h"
#include "interpreters/emotion_interpreter.h"
#include "actuators/sound_intent.h"
#include "brain/behavior_context.h"
#include "core/timebase.h"
#include "actuators/mouth.h"
#include "actuators/arms.h"
#include "interpreters/sound_interpreter.h"
#include "interpreters/proximity_interpreter.h"
#include "sensors/proximity_sensor.h"

static SoundIntent g_sound_intent;
static ComfortState current_comfort;
static BehaviorContext current_context = CONTEXT_IDLE;
static BehaviorContext prev_context = CONTEXT_IDLE;

static ActionTimer scream_timer, laugh_timer;
static TransientEmotion last_transient = TRANSIENT_NONE;
static ProximityState last_proximity = PROXIMITY_FAR;
static BehaviorContext last_context = CONTEXT_IDLE;
static SpeechFlags speech_state;
static ActionTimer conversation_timer;
static ActionTimer shy_timer;
static ActionTimer listening_timer;
static ActionTimer annoyed_timer;
static ActionTimer conversation_cooldown_timer;
static ActionTimer someone_present_timer;
static ActionTimer greeting_timer;
static ActionTimer goodbye_timer;
static ActionTimer too_close_timer;
static ActionTimer lingering_timer;   // 30s nearby → uncomfortable
static ActionTimer lingering_time_ms;
static ActionTimer boredom_timer;     // 5min no change → bored
static bool quiet_prev = false;
static bool boredom_triggered = false;

static bool conversation_sound_played = false;
static bool goodbye_sound_played = false;
static bool lingering_sound_played = false;


BehaviorContext system_controller_get_context(void) {
    return current_context;
}

const SoundIntent* system_controller_get_sound_intent(void)
{
    return &g_sound_intent;
}


void system_controller_init(void)
{
    timer_start(&boredom_timer, millis(), 300000);
}

void system_controller_update(uint32_t now_ms)
{
    EyesIntent intent = {};
    ArmsIntent arms_intent = {};

    // --------------------------
    // Reset sound intent
    // --------------------------
    g_sound_intent.play = false;
    g_sound_intent.pattern = SOUND_NONE;
    g_sound_intent.intensity = 0;

    // reset arms intent
    arms_intent.pose = ARMS_IDLE;
    arms_intent.one_shot = false;

    // --------------------------
    // Base geometry
    // --------------------------
    intent.eye_height_L = EYE_BASE_HEIGHT;
    intent.eye_height_R = EYE_BASE_HEIGHT;
    intent.eye_width_L  = EYE_BASE_WIDTH;
    intent.eye_width_R  = EYE_BASE_WIDTH;

    speech_state.quiet = true;

    if (now_ms < 3000) return;

    // --------------------------
    // Gather state inputs
    // --------------------------
    ComfortFlags comfort = comfort_interpreter_get_flags();
    LightFlags light = light_interpreter_get_flags();
    EmotionState emo = emotion_interpreter_get_state();
    SoundFlags sound = sound_interpreter_get_flags();
    BehaviorState behavior = behavior_fsm_get_state();
    ProximityFlags proximity = proximity_interpreter_get_flags();

    // --------------------------
    // Update timers from transient edges
    // --------------------------
    if (emo.transient == TRANSIENT_MUSIC &&
        last_transient != TRANSIENT_MUSIC)
    {
        timer_start(&laugh_timer, now_ms, 750);
    }

    if (emo.transient == TRANSIENT_STARTLED &&
        last_transient != TRANSIENT_STARTLED)
        
    {
        timer_start(&scream_timer, now_ms, 500);
    }

    last_transient = emo.transient;

    if (proximity.nearby || proximity.too_close)
        timer_start(&someone_present_timer, now_ms, 60000);

    if (proximity.too_close) {
        intent.override_mood = true;
        intent.mood = EYES_MOOD_SAD;
        intent.tremble = true;
        arms_intent.pose = ARMS_ATTACK;
        arms_intent.one_shot = false;
    if (timer_active(&too_close_timer, now_ms)) {
        g_sound_intent.play = true;
        g_sound_intent.pattern = SOUND_BRIEF_REACT;
    }
}

    if (timer_active(&goodbye_timer, now_ms)) {
    intent.override_mood = true;
    intent.mood = EYES_MOOD_SAD;
    arms_intent.pose = ARMS_WAVE;
    arms_intent.one_shot = false;
    if (!goodbye_sound_played) {
        g_sound_intent.play = true;
        g_sound_intent.pattern = SOUND_BRIEF_REACT;
        goodbye_sound_played = true;
    }
}

if (!timer_active(&goodbye_timer, now_ms)) {
    goodbye_sound_played = false;
}

if((!timer_active(&lingering_timer, now_ms) && proximity.nearby) || (!timer_active(&lingering_timer, now_ms) && proximity.too_close)) {
    current_context = CONTEXT_LINGERING;
    timer_start(&lingering_time_ms, now_ms, 3000);
    intent.override_mood = true;
    intent.mood = EYES_MOOD_SAD;

    if(timer_active(&lingering_time_ms, now_ms)) {
        arms_intent.pose = ARMS_HOT;
        arms_intent.one_shot = false;
        if (!lingering_sound_played) {
        g_sound_intent.play = true;
        g_sound_intent.pattern = SOUND_BRIEF_REACT;
        lingering_sound_played = true;
    } 

}
}

if (timer_active(&lingering_timer, now_ms)) {
    lingering_sound_played = false;
}
    // --------------------------
    // Determine behavior context
    // --------------------------

    if (emo.transient != TRANSIENT_STARTLED && emo.base != EMOTION_ANGRY) {
    if (sound.noise)
        current_context = CONTEXT_ANNOYED;
    else if (sound.talking) {
        current_context = CONTEXT_LISTENING;
        speech_state.quiet = true;
        timer_start(&listening_timer, now_ms, 2500);
    } else if (timer_active(&listening_timer, now_ms)) {
        current_context = CONTEXT_LISTENING;
    } else {
        current_context = CONTEXT_IDLE;
        speech_state.quiet = true;
    }
}

        // --- Detect context transitions ---
        
    if (current_context == CONTEXT_ANNOYED &&
        last_context != CONTEXT_ANNOYED)
    {
        timer_start(&annoyed_timer, now_ms, 600);
    }

    last_context = current_context;

    if(transition_true(sound.quiet, &quiet_prev)) {

    
    if (timer_active(&conversation_cooldown_timer, now_ms))
        return;

    if(prev_context == CONTEXT_LISTENING) {

        if(chance_percent(85)) {

            timer_start(&conversation_timer, now_ms, 2000);
            current_context = CONTEXT_CONVERSING;
            speech_state.response = true;
            conversation_sound_played = false;

        } else {

            timer_start(&shy_timer, now_ms, 1200);
            current_context = CONTEXT_SHY;
            speech_state.shy_response = true;
        }

        // Start cooldown
        timer_start(&conversation_cooldown_timer, now_ms, 3000);
    }
}



    // --------------------------
    // Base emotional rendering
    // --------------------------
    if (emo.base == EMOTION_SAD)
    {
        intent.override_mood = true;
        intent.mood = EYES_MOOD_SAD;
    }

    // --------------------------
    // Base behavior rendering
    // --------------------------
    if (comfort.overheated)
    {
        intent.base = EYES_BASE_AWAKE;
        intent.override_mood = true;
        intent.mood = EYES_MOOD_TIRED;
    }
    else if (behavior == BEHAVIOR_ASLEEP)
    {
        if (light.semi_bright || current_context == CONTEXT_LISTENING)
            intent.base = EYES_BASE_HALF_AWAKE;
        else
            intent.base = EYES_BASE_SLEEP; 
    }
    else
    {
        intent.base = EYES_BASE_AWAKE;
    }

    // --------------------------
    // Transient emotion overrides
    // --------------------------
    if (emo.transient == TRANSIENT_STARTLED)
    {
        current_context = CONTEXT_SCARED;
        intent.base = EYES_BASE_AWAKE;
        intent.override_mood = true;
        intent.mood = EYES_MOOD_SAD;
        intent.tremble = true;
        arms_intent.pose = ARMS_GOF_OUT;
        arms_intent.one_shot = false;
        intent.override_eye_height = true;
        intent.eye_height_L = EYE_BASE_HEIGHT + 20;
        intent.eye_height_R = EYE_BASE_HEIGHT + 20;
        intent.eye_width_L = EYE_BASE_HEIGHT - 20;
        intent.eye_width_R = EYE_BASE_HEIGHT - 20;

        if (timer_active(&scream_timer, now_ms))
        {
            g_sound_intent.play = true;
            g_sound_intent.pattern = SOUND_BRIEF_REACT;
        }
    }

    if (emo.transient == TRANSIENT_MUSIC)
    {
        intent.base = EYES_BASE_AWAKE;
        intent.override_mood = true;
        intent.mood = EYES_MOOD_HAPPY;

        if (timer_active(&laugh_timer, now_ms))
        {
            g_sound_intent.play = true;
            g_sound_intent.pattern = SOUND_LAUGH;
        }
    }

    // Conversation timers override context
    if (timer_active(&conversation_timer, now_ms))
    {
        current_context = CONTEXT_CONVERSING;
    }
    else if (timer_active(&shy_timer, now_ms))
    {
        current_context = CONTEXT_SHY;
    }

    if (!timer_active(&conversation_timer, now_ms))
    {
        conversation_sound_played = false;
    }


    // --------------------------
    // Context overlays
    // --------------------------
    if (current_context == CONTEXT_LISTENING) {

        if (behavior == BEHAVIOR_ASLEEP) {
            intent.override_mood = true;
            intent.mood = EYES_MOOD_ANGRY;

            arms_intent.pose = ARMS_ATTACK;
            arms_intent.one_shot = false;

            intent.override_eye_height = true;
            intent.eye_height_L += 6;
            intent.eye_height_R += 6;
        } else {
            intent.override_mood = true;
            intent.mood = EYES_MOOD_HAPPY;

            arms_intent.pose = ARMS_WAVE;
            arms_intent.one_shot = false;

            intent.override_eye_height = true;
            intent.eye_height_L += 6;
            intent.eye_height_R += 6;
        }

    }

    if (timer_active(&greeting_timer, now_ms)) {
        intent.override_mood = true;
        intent.mood = EYES_MOOD_HAPPY;
        arms_intent.pose = ARMS_WAVE;
        arms_intent.one_shot = false;
        intent.override_eye_height = true;
        intent.eye_height_L += 6;
        intent.eye_height_R += 6;
        g_sound_intent.play = true;
        g_sound_intent.pattern = SOUND_LAUGH;
    }

    if (current_context == CONTEXT_ANNOYED)
    {
        intent.override_mood = true;
        intent.mood = EYES_MOOD_ANGRY;
        arms_intent.pose = ARMS_ATTACK;
        arms_intent.one_shot = false;
        
        // Change later to annoyed sounds
        if (timer_active(&annoyed_timer, now_ms))
        {
            g_sound_intent.play = true;
            g_sound_intent.pattern = SOUND_BRIEF_REACT;
        }
    }

        if (current_context == CONTEXT_CONVERSING)
    {
        intent.override_mood = true;
        intent.mood = EYES_MOOD_HAPPY;

        // Talking animation tweak
        intent.override_eye_height = true;
        intent.eye_height_L -= 10;
        intent.eye_height_R -= 10;

        arms_intent.pose = ARMS_GOF_OUT;
        arms_intent.one_shot = false;

        if (behavior == BEHAVIOR_ASLEEP) {
        intent.mood = EYES_MOOD_ANGRY;  // ← angry when it actually responds
    } else {
        intent.mood = EYES_MOOD_HAPPY;
    }

        if (!timer_active(&conversation_timer, now_ms))
            timer_stop(&conversation_timer);

        // Optional temporary talking sound

        if (!conversation_sound_played)
        {
            g_sound_intent.play = true;
            g_sound_intent.pattern = SOUND_LAUGH;
            conversation_sound_played = true;
        }
     
    }



    if (current_context == CONTEXT_SHY)
    {
        intent.override_mood = true;
        intent.mood = EYES_MOOD_SAD;

        intent.override_eye_height = true;
        intent.eye_height_L -= 20;
        intent.eye_height_R -= 20;
        arms_intent.pose = ARMS_HOT;
        arms_intent.one_shot = false;
    }



    // --------------------------
    // Sleep escalation rule
    // --------------------------
    if (behavior == BEHAVIOR_ASLEEP && (sound.music || sound.noise))
    {
        intent.base = EYES_BASE_AWAKE;
        intent.override_mood = true;
        intent.mood = EYES_MOOD_ANGRY;
        arms_intent.pose = ARMS_ATTACK;
        arms_intent.one_shot = false;

        // Change later to annoyed sounds
        if (timer_active(&scream_timer, now_ms))
        {
            g_sound_intent.play = true;
            g_sound_intent.pattern = SOUND_BRIEF_REACT;
        }
    }


    // Boredom // // 

    // // // // // // 
if (!timer_active(&boredom_timer, now_ms) && !boredom_triggered) {
    boredom_triggered = true;
}

if (timer_active(&boredom_timer, now_ms)) {
    boredom_triggered = false;  // reset when timer restarts
}


if(boredom_triggered) {
    if(chance_percent(80)) {
        behavior_fsm_set_state(BEHAVIOR_BORED);
    } else {
        behavior_fsm_set_state(BEHAVIOR_ASLEEP);
    }
}


if (behavior == BEHAVIOR_BORED) {
    current_context = CONTEXT_BORED;
    intent.override_mood = true;
    intent.mood = EYES_MOOD_SAD;
    arms_intent.pose = ARMS_IDLE;
    arms_intent.one_shot = false;
}
    // --------------------------
    // Physical modifiers
    // --------------------------
    intent.sweat = comfort.hot || comfort.overheated || emo.transient == TRANSIENT_STARTLED;
    intent.tremble = comfort.cold || comfort.chilled || emo.transient == TRANSIENT_STARTLED;

    if (light.too_bright)
    {
        intent.squint = true;
        intent.override_eye_height = true;
        intent.eye_height_L = SQUINT;
        intent.eye_height_R = SQUINT;
    }
    
    eyes_set_intent(&intent);
    arms_set_intent(&arms_intent);
    prev_context = current_context;
}


void system_controller_handle_event(const Event *event)
{
    switch (event->type)
    {
        case EVENT_TEMP_ENTER_HOT:
            current_comfort = COMFORT_HOT;
            Serial.println("Controller: entered HOT");
            boredom_triggered = false;
            behavior_fsm_set_state(BEHAVIOR_AWAKE);
            break;

        case EVENT_TEMP_EXIT_HOT:
            Serial.println("Controller: exited HOT (phew)");
            break;

        case EVENT_TEMP_ENTER_COMFY:
            Serial.println("Is comfy.");
            current_comfort = COMFORT_COMFY;
            
            break;

        case EVENT_TEMP_ENTER_COLD:
            current_comfort = COMFORT_COLD;
            Serial.println("Controller: entered COLD");
            boredom_triggered = false;
            behavior_fsm_set_state(BEHAVIOR_AWAKE);
            
            break;

        case EVENT_TEMP_EXIT_COLD:
            Serial.println("Controller: exited COLD");
            break;

        case EVENT_SOUND_MUSIC_DETECTED: 
            Serial.println("Oh? is music?");
            boredom_triggered = false;
            behavior_fsm_set_state(BEHAVIOR_AWAKE);
            break;  
            
        case EVENT_SOUND_PEAK:
           // Serial.println("PEAK");
            break;

        case EVENT_SOUND_BURST:
            Serial.println("BURST");
            boredom_triggered = false;
            behavior_fsm_set_state(BEHAVIOR_AWAKE);
            break;

        case EVENT_SOUND_GENERAL_NOISE:
            Serial.println("NOISY!!");
            boredom_triggered = false;
            behavior_fsm_set_state(BEHAVIOR_AWAKE);
            break;

        case EVENT_SOUND_TALKING:
            Serial.println("Is talking?");
            boredom_triggered = false;
            behavior_fsm_set_state(BEHAVIOR_AWAKE);
            break;

        case EVENT_PROX_FAR:
            last_proximity = PROXIMITY_FAR;
            timer_start(&goodbye_timer, event->timestamp_ms, 3000);
            timer_start(&boredom_timer, event->timestamp_ms, 300000);
            timer_stop(&lingering_timer);
            break;

        case EVENT_PROX_CLOSE:
    if (last_proximity == PROXIMITY_FAR) {
        timer_start(&greeting_timer, event->timestamp_ms, 3000);
        timer_start(&lingering_timer, event->timestamp_ms, 30000);
        timer_start(&boredom_timer, event->timestamp_ms, 300000);
    }

    last_proximity = PROXIMITY_NEARBY;
    boredom_triggered = false;
    behavior_fsm_set_state(BEHAVIOR_AWAKE);  
    break;

    case EVENT_PROX_TOO_CLOSE:
    last_proximity = PROXIMITY_TOO_CLOSE;
    timer_start(&too_close_timer, event->timestamp_ms, 2000);
    timer_start(&boredom_timer, event->timestamp_ms, 300000);
    boredom_triggered = false;
    behavior_fsm_set_state(BEHAVIOR_AWAKE);
    break;
        default:
            break;
    }
}
