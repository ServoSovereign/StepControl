#pragma once
#include <Arduino.h>
#include "Stew.h"

void initDriver();
void initEncoder();

void setDirMotor(int Direction);
void readEncoder();
void runStepMotor(uint32_t numberOfPulses);
void printEncoderInfo();

uint32_t getPulses(uint32_t numberOfRevolution);
