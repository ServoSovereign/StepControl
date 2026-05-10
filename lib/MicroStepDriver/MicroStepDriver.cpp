#include "MicroStepDriver.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

static const uint8 enablePin     = 11;
static const uint8 dirrectionPin = 10;
static const uint8 pulsePin      = 9;

static const uint16 stepDelay    = 200;
static const uint32 baurdRate    = 9600;
static const uint16 PULSES_PER_REVOLUTION = 1600;


void initDriver(){
    Serial.begin(baurdRate);
    delay(1000);
    
    pinMode(enablePin, OUTPUT);
    pinMode(dirrectionPin, OUTPUT);
    pinMode(pulsePin, OUTPUT);

    digitalWrite(enablePin, LOW);
    Serial.println("Driver OK"); 
}

uint32 getPulses(uint32 Revolutions){
    return(Revolutions*PULSES_PER_REVOLUTION);
}

void runStepMotor(uint32 numberOfPulses){
    for(uint32 i=0; i<numberOfPulses; i++){
        digitalWrite(pulsePin, HIGH);
        delayMicroseconds(stepDelay);
        digitalWrite(pulsePin, LOW);
        delayMicroseconds(stepDelay);
    }
}