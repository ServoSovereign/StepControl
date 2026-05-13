#include <Arduino.h>
#include "Stew.h"
#include "MicroStepDriver.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;

extern volatile int32 encoderCount;

void setup() {
    initDriver();
    initEncoder();
}

void loop() {
    //Getg direction
    Serial.println("Input Direction: 0 to forward");
    int8_t DIRECTION=getSerialString().toInt();
    setDirMotor(DIRECTION);
    //Get revolution
    Serial.println("Input Revolution: ");
    uint16 NUM=getSerialString().toInt();
    //Convert to pulses
    uint32 PULSES=getPulses(NUM);

    noInterrupts();
    encoderCount = 0;
    interrupts();
    
    //Run with said pulses
    runStepMotor(PULSES);
    delay(50);
    //Encoder
    printEncoderInfo();
    //Confirm status
    Serial.println("Successful\n");
    delay(1000);
}