#pragma once
#include <Arduino.h>
#include "Stew.h"

void initDriver();
void initEncoder();

void setDirMotor(int Direction);
void readEncoder();
void runStepMotor(uint32_t numberOfPulses);
void printEncoderInfo();

int32_t readCountEncoder();
int32_t readRevEncoder();
int32_t readAngleEncoder();
int32_t readDirEncoder();
uint32_t getPulses(uint32_t numberOfRevolution);
