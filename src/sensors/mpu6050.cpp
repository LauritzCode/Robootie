#include "mpu6050.h"
#include "core/event_queue.h"
#include "brain/behavior_fsm.h"
#include "system/system_controller.h"
#include "brain/behavior_context.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>
#include <math.h>

static Adafruit_MPU6050 mpu;
static bool mpu_ready = false;

// ── tuning ────────────────────────────────────────────────────────────────────
// Shake: gyro magnitude (rad/s) must exceed this for MIN_SHAKE_STREAK samples
static const float    SHAKE_GYRO_THRESH = 0.6f;
static const uint8_t  SHAKE_MIN_STREAK  = 4;
static const uint32_t SHAKE_COOLDOWN_MS = 2000;

// Pick up / put down: accel magnitude deviation from ~9.81 m/s² sustained
static const float    PICKUP_DEV_THRESH = 2.0f;
static const uint32_t PICKUP_SUSTAIN_MS = 600;

// Flip: AZ sign changes while accel mag is substantial (rules out free fall)
static const float    FLIP_ACCEL_MIN   = 5.0f;

// Poll intervals (ms) — slower when idle/asleep, faster when active
static const uint32_t INTERVAL_ASLEEP  = 500;
static const uint32_t INTERVAL_IDLE    = 200;
static const uint32_t INTERVAL_ACTIVE  = 80;   // shaking or picked up

// ── state ─────────────────────────────────────────────────────────────────────
static MotionFlags flags;

static float    prev_accel_mag   = 9.81f;
static uint8_t  shake_streak     = 0;
static bool     az_was_positive  = true;
static bool     pickup_candidate = false;
static uint32_t pickup_start_ms  = 0;
static uint32_t last_shake_ms    = 0;
static uint32_t last_pickup_ms   = 0;
static uint32_t last_putdown_ms  = 0;
static uint32_t last_read_ms     = 0;

static inline float vec_mag(float x, float y, float z)
{
    return sqrtf(x * x + y * y + z * z);
}

void motion_sensor_init(void)
{
    if (!mpu.begin()) {
        Serial.println("MPU6050 init failed!");
        return;
    }
    flags.shaking   = false;
    flags.picked_up = false;
    flags.flipped   = false;
    mpu_ready = true;
    Serial.println("MPU6050 ready.");
}

void motion_sensor_update(uint32_t now_ms)
{
    if (!mpu_ready) return;

    // ── Rate limiting ─────────────────────────────────────────────────────────
    BehaviorState behavior = behavior_fsm_get_state();

    uint32_t interval;
    if (flags.shaking || flags.picked_up)
        interval = INTERVAL_ACTIVE;
    else if (behavior == BEHAVIOR_ASLEEP)
        interval = INTERVAL_ASLEEP;
    else
        interval = INTERVAL_IDLE;

    if (now_ms - last_read_ms < interval) return;
    last_read_ms = now_ms;

    // ── Read sensor ───────────────────────────────────────────────────────────
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float ax = a.acceleration.x;
    float ay = a.acceleration.y;
    float az = a.acceleration.z;
    float gx = g.gyro.x;
    float gy = g.gyro.y;
    float gz = g.gyro.z;

    float amag = vec_mag(ax, ay, az);
    float gmag = vec_mag(gx, gy, gz);

    // ── Shake ─────────────────────────────────────────────────────────────────
    bool was_shaking = flags.shaking;

    if (gmag > SHAKE_GYRO_THRESH)
        shake_streak = (shake_streak < 255) ? shake_streak + 1 : 255;
    else
        shake_streak = 0;

    flags.shaking = (shake_streak >= SHAKE_MIN_STREAK);

    if (flags.shaking && !was_shaking &&
        (now_ms - last_shake_ms > SHAKE_COOLDOWN_MS))
    {
        last_shake_ms = now_ms;
        Event e;
        e.type         = EVENT_MOTION_SHAKEN;
        e.timestamp_ms = now_ms;
        e.value        = (uint16_t)(gmag * 100);
        event_queue_push(e);
    }

    // ── Pick up / put down ────────────────────────────────────────────────────
    bool disturbed = (fabsf(amag - 9.81f) > PICKUP_DEV_THRESH);

    if (disturbed) {
        if (!pickup_candidate) {
            pickup_candidate = true;
            pickup_start_ms  = now_ms;
        }
        if (!flags.picked_up &&
            (now_ms - pickup_start_ms > PICKUP_SUSTAIN_MS) &&
            (now_ms - last_pickup_ms  > PICKUP_SUSTAIN_MS))
        {
            last_pickup_ms  = now_ms;
            flags.picked_up = true;
            Event e;
            e.type         = EVENT_MOTION_PICKED_UP;
            e.timestamp_ms = now_ms;
            e.value        = 0;
            event_queue_push(e);
        }
    } else {
        if (flags.picked_up && (now_ms - last_putdown_ms > 2000)) {
            flags.picked_up = false;
            last_putdown_ms = now_ms;
            Event e;
            e.type         = EVENT_MOTION_PUT_DOWN;
            e.timestamp_ms = now_ms;
            e.value        = 0;
            event_queue_push(e);
        }
        pickup_candidate = false;
    }

    // ── Flip ──────────────────────────────────────────────────────────────────
    bool az_positive_now = (az > 0.0f);
    if (az_positive_now != az_was_positive && amag > FLIP_ACCEL_MIN)
    {
        flags.flipped = !az_positive_now;   // upside down when AZ goes negative
        Event e;
        e.type         = EVENT_MOTION_FLIPPED;
        e.timestamp_ms = now_ms;
        e.value        = flags.flipped ? 1 : 0;
        event_queue_push(e);
    }
    az_was_positive = az_positive_now;

    prev_accel_mag = amag;
}

MotionFlags motion_sensor_get_flags(void)
{
    return flags;
}
