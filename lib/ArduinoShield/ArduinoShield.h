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

void runMotorChannelX(int32_t numberOfPulses);
void runMotorChannelY(int32_t numberOfPulses);
void runMotorChannelZ(int32_t numberOfPulses);
void runMotorChannelA(int32_t numberOfPulses);

void setDirectionChannelX(bool Bit);
void setDirectionChannelY(bool Bit);
void setDirectionChannelZ(bool Bit);
void setDirectionChannelA(bool Bit);

void testDirectionChannelX();
void testDirectionChannelY();
void testDirectionChannelZ();
void testDirectionChannelA();