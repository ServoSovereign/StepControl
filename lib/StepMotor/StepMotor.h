//Hardware:
    //Double step motors with a wood plank
    //Inventor: Khai
#pragma once
#include <Arduino.h>

//Use both of these inside void setup
void initDriver();
void resetMotor();

//Use either of these inside void loop
void serialMotorMode();
void manualMotorMode();

//Functions
String getStringSerial();
void getDistance();
void convertToSteps();
void distanceToMove();
void setDirection();
void runMotors(float moveDistanceX, float moveDistanceY);
void renewCoord();
void testChannelDriver();