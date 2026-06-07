#include <Arduino.h>
#include "Stew.h"
#include "ArduinoShield.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;

static int32 numberOfPulses1=0;
static int32 numberOfPulses2=0;
static int32 i=0;

void setup() {
    initDriver();
}

void loop() {
    Serial.print("Elapsed: ");
    Serial.println(i);

    testDirectionChannelY();
    testDirectionChannelZ();

    Serial.println("Get pulses Y: ");
    numberOfPulses1=getSerialString().toInt();
    Serial.println("Get pulses Z: ");
    numberOfPulses2=getSerialString().toInt();

    runMotorChannelY(numberOfPulses1);
    runMotorChannelZ(numberOfPulses2);

    i++;
}