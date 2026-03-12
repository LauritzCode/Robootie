#include "proximity_sensor.h"
#include "core/event.h"
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void proximity_init(void) {
    
    if (!lox.begin()) {
        Serial.println("VL53L0X init failed!");
        return;
    }
    
    lox.startRangeContinuous();
     Serial.println("VL53L0X ready.");
}

void proximity_update(uint32_t now_ms) {
 
    uint16_t distance = lox.readRange();
    Serial.println(distance);
    }
