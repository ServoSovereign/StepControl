#include <Arduino.h>
#include "ArduinoShield.h"
#include "MicroStepDriver.h"

void setup() {
  initDriver();
  resetMotor();
}

void loop() {
  serialMotorMode();
  delay(1000);
}