#include <Arduino.h>
#include "arms.h"
#include "config/pins.h"
#include <Servo.h>

Servo leftArm;
Servo rightArm;

uint32_t last_move_time = 0;
bool pose = false;

void armsTestInit()
{
    leftArm.attach(9);
    rightArm.attach(8);
}

void armsTest()
{
    uint32_t now = millis();

    if (now - last_move_time >= 500)
    {
        last_move_time = now;

        if (!pose)
        {
            leftArm.write(30);
            rightArm.write(150);
        }
        else
        {
            leftArm.write(120);
            rightArm.write(60);
        }

        pose = !pose;
    }
}