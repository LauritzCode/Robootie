#pragma once


// Light related 


/*
On average, darkness varies between 600 - 800 
Default brightness is about 230-240. Point a light directly and it goes to 40 or so. 

*/
#define LIGHT_DARK_THRESHOLD 500
#define LIGHT_TOO_BRIGHT_THRESHOLD 120
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

 #define SQUINT 20
 #define EYE_BASE_HEIGHT 36
 #define EYE_BASE_WIDTH 36

 // Proximity configs

 #define PROX_TOO_FAR 500
 #define PROX_CLOSE 250
 #define PROX_TOO_CLOSE 150 