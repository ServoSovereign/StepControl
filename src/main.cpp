#include <Arduino.h>
#include "Stew.h"
#include "MicroStepDriver.h"

#define MAX_ITERATION 10

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

void setup() {
    initDriver();
}

void loop() {
    Serial.println("Input Revolution: ");
    uint16 NUM=getSerialString().toInt();
    uint32 STEPS=getRevolutions(NUM);
    runStepMotor(STEPS);

    Serial.println("Successful");
    delay(1000);
}