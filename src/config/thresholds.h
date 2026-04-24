#pragma once


// Light related 


/*
On average, darkness varies between 600 - 800 
Default brightness is about 230-240. Point a light directly and it goes to 40 or so. 

*/
#define LIGHT_DARK_THRESHOLD 500
#define LIGHT_TOO_BRIGHT_THRESHOLD 70
#define LIGHT_SEMI_BRIGHT_THRESHOLD_MIN 501
#define LIGHT_SEMI_BRIGHT_THRESHOLD_MAX 600



// Temp related 

#define TEMP_COLD_THRESHOLD 5
#define TEMP_HOT_THRESHOLD 25

#define HOT_GRACE_MS 5000
#define HOT_CONFIRM_MS 10000

#define CHILL_GRACE_MS 5000
#define CHILL_CONFIRM_MS 30000


// Eyes configs

 #define SQUINT 36
 #define EYE_BASE_HEIGHT 36
 #define EYE_BASE_WIDTH 36

 // Proximity configs
 /*
  Hardware limits (VL53L0X mounted on Robootie's front):
    350mm — absolute maximum reliable detection range; anything beyond reads as noise/max
     85mm — physical crash threshold; object is right at the bumper, imminent collision
    150mm — "looking distance": natural curiosity zone — close enough to inspect,
             far enough to react. Useful for autonomous drive behaviours:
             stop & look, back away to inspect, or hold distance from a person.
  */

 #define PROX_TOO_FAR 500
 #define PROX_CLOSE 200         // enter "nearby" when closer than this (mm)
 #define PROX_NEARBY_EXIT 350   // exit "nearby" → FAR only when further than this (hysteresis)
 #define PROX_TOO_CLOSE 100      // crash zone — stop immediately when driving autonomously
 #define PROX_CURIOSITY 150     // curiosity/inspect distance for autonomous behaviour

 #define GOODBYE_COOLDOWN_MS 8000   // min ms between goodbye reactions