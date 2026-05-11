#pragma once
#include <Arduino.h>
#include "Stew.h"

void initDriver();
void readEncoder();
void runStepMotor(uint32_t numberOfSteps);
void printEncoderInfo();

uint32_t getPulses(uint32_t numberOfPulses);
