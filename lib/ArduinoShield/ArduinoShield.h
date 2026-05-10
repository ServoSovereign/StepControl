#pragma once
#include <Arduino.h>
#include "Stew.h"
//Use both of these inside void setup
void initDriver();
void resetMotor();

//Use either of these inside void loop
void serialMotorMode();
void manualMotorMode();

//Functions
void getDistance();
void convertToSteps();
void distanceToMove();
void setDirection();
void runMotors(float moveDistanceX, float moveDistanceY);
void renewCoord();
void testChannelDriver();