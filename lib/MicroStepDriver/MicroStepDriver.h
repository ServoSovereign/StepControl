#pragma once
#include <Arduino.h>
#include "Stew.h"

void initDriver();
void runStepMotor(uint32_t numberOfSteps);

uint32_t getRevolutions(uint32_t numberOfPulses);
