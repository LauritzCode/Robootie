# Robootie Personality Roadmap

## Overview

Two new behaviour modes trigger after 2 minutes of inactivity (replacing the current
sleep-only boredom timer). The split is now:

- 33% → BEHAVIOR_ASLEEP (existing)
- 33% → BEHAVIOR_BORED (new)
- 33% → BEHAVIOR_EXPLORE (new)

`BEHAVIOR_EXPLORE` needs to be added to the `behavior_fsm` enum.

---

## Bored Mode

### What runs
- `SOUND_BORED_SING` buzzer pattern plays every 10–15s (random interval).
  Clean bird-like melodic beeping — random notes within a pleasant scale,
  short pauses between, NOT noise-like.
- LCD cycles through a new bored phrase pool every ~8s.
- Arms idle.

### Exit triggers (any → BEHAVIOR_AWAKE + restart boredom timer)
- EVENT_SOUND_TALKING, EVENT_SOUND_MUSIC_DETECTED
- EVENT_SOUND_GENERAL_NOISE, EVENT_SOUND_BURST
- EVENT_MOTION_SHAKEN, EVENT_MOTION_FLIPPED
- Own timer: 3–5 minutes random → BEHAVIOR_ASLEEP

### Files
- `actuators/buzzer.cpp` — add SOUND_BORED_SING pattern
- `brain/data.h` — add bored phrase pool
- `system_controller.cpp` — render bored state, exit logic

---

## Explore Mode

### New module: `src/brain/explore.cpp` + `explore.h`

Called from `main.cpp` loop as `explore_update(now)`.
Has its own `explore_handle_event()` registered in the event dispatcher.
The handler immediately returns if `behavior_fsm_get_state() != BEHAVIOR_EXPLORE`.

### Internal state machine

```
EXPLORE_SCAN_SWEEP
       |
  (15% chance: EXPLORE_SILLY_SPIN → weee full 360°)
       |
EXPLORE_PICK_DIRECTION
       |
EXPLORE_DRIVING ────── obstacle < PROX_TOO_CLOSE ──→ EXPLORE_BACKUP ──→ SCAN_SWEEP
       |
  proximity NEARBY polled each tick (not event-driven)
       |
  1/4 chance: EXPLORE_GREETING
       |──────────────────────────────────────────────────┐
  distance changed (>30mm in 3s)                 no change
       |                                                  |
  EXPLORE_HUMAN_REACT                        EXPLORE_OBJECT_REACT
  → BEHAVIOR_AWAKE                           → drive away OR linger briefly
  (normal social mode)                       → resume SCAN_SWEEP
       |
  10-min timer → BEHAVIOR_ASLEEP
```

### SCAN_SWEEP detail
1. Spin LEFT at speed 100 for ~600ms → record `left_dist`
2. Spin RIGHT for ~600ms → return to centre, record `centre_dist`
3. Spin RIGHT for ~600ms → record `right_dist`
4. Pick direction with max clearance (or random for fun)
5. 15% chance: insert SILLY_SPIN before driving

### SILLY_SPIN
- Full LEFT spin ~2000ms (tune empirically for 360° at speed 100)
- LCD: silly phrase ("weeee!" type), happy beep
- Return to PICK_DIRECTION

### DRIVING
- Forward at speed 100
- Drive intent refreshed every loop tick
- Poll proximity each tick:
  - distance < PROX_TOO_CLOSE (100mm) → BACKUP
  - proximity_state == PROXIMITY_NEARBY → GREETING (or re-scan if no greet roll)
- Random drive duration 4–12s before returning to SCAN_SWEEP

### GREETING sequence (during explore)
1. Stop motors
2. Wave arms, play hello beep, show greeting LCD (existing phrases)
3. Record current distance
4. Wait 3s, sample every 500ms
5. If any sample differs >30mm → HUMAN_REACT:
   - LCD: proud "it's a human!" phrase (new pool needed)
   - transition to BEHAVIOR_AWAKE — normal social interaction takes over
6. If no change → OBJECT_REACT:
   - LCD: "oh just a thing" phrase (new pool needed)
   - 50/50: drive away immediately OR circle slowly 2s then drive away
   - Resume explore

### Interrupt table
| Trigger | Action |
|---|---|
| EVENT_MOTION_SHAKEN or FLIPPED | immediate motor stop → BEHAVIOR_AWAKE |
| EVENT_SOUND_* (any) | motor stop → BEHAVIOR_AWAKE |
| BT command `!q` | motor stop → BEHAVIOR_AWAKE (safety quit) |
| 10-minute overall timer | motor stop → BEHAVIOR_ASLEEP |

### Note: proximity polling vs events
During EXPLORE_DRIVING, proximity is polled directly each tick rather than
relying on EVENT_PROX_CLOSE. This gives the explore state machine fine-grained
control over WHEN in its flow to act on proximity. EVENT_PROX_CLOSE still fires
normally and system_controller's greeting_timer runs in parallel — they both
produce greeting behaviour simultaneously, which is complementary not conflicting.

---

## Bluetooth Commands (additions)

| Command | Byte | Function |
|---|---|---|
| `!e` | 'e' | Start explore immediately (test trigger) |
| `!q` | 'q' | Quit explore, stop motors, return to manual (safety) |
| `!x` | 'x' | Trigger one SILLY_SPIN (test) |
| `!g` | 'g' | Trigger GREETING sequence at current distance (test) |

---

## Angry Phrases (implemented)

When Robootie is woken (burst or normal grumpy wake), angry phrases cycle
on the LCD every ~10 seconds for the duration of the angry timer.

- Burst wake: 60 seconds of angry
- Normal grumpy wake (50% chance): 15 seconds of angry

Implementation: `MOUTH_ANGRY` state in mouth.cpp, cycling timer resets
`g_current` every 10s to force a re-render with a new random phrase.
`system_controller_is_woken_angry(now_ms)` getter exposes the timer state.

---

## Architecture: Event Dispatcher Pattern

`explore_handle_event()` is registered directly in `event_dispatcher.cpp`,
same as every other module. It returns immediately if not in BEHAVIOR_EXPLORE.

Reasoning: system_controller forwarding would require it to #include explore.h,
coupling a general orchestration module to a specific behaviour module. The
dispatcher pattern keeps modules independent. When both handlers fire for the
same event (e.g. sound interrupt during explore), they converge on the same
result (BEHAVIOR_AWAKE) — complementary, not conflicting.

---

## Hardware Notes (VL53L0X, front-mounted)

| Distance | Meaning |
|---|---|
| 350mm | Absolute max reliable detection range |
| 200mm | Enter NEARBY zone (social detection) |
| 150mm | PROX_CURIOSITY — natural inspect/curiosity distance for autonomous behaviours |
| 100mm | PROX_TOO_CLOSE — crash zone, stop immediately when driving autonomously |
| 85mm | Physical bumper — object is right at Robootie's front face |

---

## Files to Touch (explore + bored implementation)

| File | Change |
|---|---|
| `brain/behavior_fsm.h` | Add BEHAVIOR_EXPLORE to enum |
| `brain/explore.cpp/.h` | New module — full autonomous state machine |
| `brain/data.h` | Bored phrases, explore human-detect phrases, explore object phrases, explore silly phrases |
| `system/bluetooth.h/.cpp` | Add !e !q !x !g commands |
| `system/system_controller.cpp` | 3-way boredom split, bored rendering, bored exit on stim |
| `actuators/buzzer.cpp` | SOUND_BORED_SING pattern |
| `main.cpp` | Add explore_update(now) to loop, register explore_handle_event |
| `core/event_dispatcher.cpp` | Register explore_handle_event() |
