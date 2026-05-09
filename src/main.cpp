#include <Arduino.h>
#include "StepMotor.h"

void setup() {
  initDriver();
  resetMotor();
}

void loop() {
  serialMotorMode();
  delay(1000);
}