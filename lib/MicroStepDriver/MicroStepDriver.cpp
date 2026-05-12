#include "MicroStepDriver.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef int32_t int32;

static const uint8 enablePin    = 5;
static const uint8 directionPin = 6;
static const uint8 pulsePin     = 7;
static const uint8 encoderPinA  = 2;
static const uint8 encoderPinB  = 3;  
static const uint8 microSteps   = 8;
static const uint16 pulseDelay  = 200;
static const uint16 pulsesPerRevolutionMotor = 1600;
static const uint16 pulsesPerRevolutionEncoder= 400;
static const uint16 countsPerRevolution = 400;
static const uint32 baudRate    = 115200;

volatile int32 encoderCount     = 0;

void initDriver(){
    Serial.begin(baudRate);
    delay(1000);
    
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);

    pinMode(enablePin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(pulsePin, OUTPUT);

    attachInterrupt(
        digitalPinToInterrupt(encoderPinA), 
        readEncoder, 
        CHANGE);
    attachInterrupt(
        digitalPinToInterrupt(encoderPinB),
        readEncoder,
        CHANGE);
    
    digitalWrite(enablePin, LOW);
    digitalWrite(directionPin, LOW);
    Serial.println("Driver OK"); 
}

uint32 getPulses(uint32 Revolutions){
    return(Revolutions*pulsesPerRevolutionMotor);
}

void readEncoder() {
    bool signalA = digitalRead(encoderPinA);
    bool signalB = digitalRead(encoderPinB);
}

void runStepMotor(uint32 numberOfPulses){
    for (uint32_t i = 0; i < numberOfPulses; i++) {
        digitalWrite(pulsePin, HIGH);
        delayMicroseconds(pulseDelay);
        digitalWrite(pulsePin, LOW);
        delayMicroseconds(pulseDelay);
    }
}

void printEncoderInfo(){
    noInterrupts();
    int32 COUNT = encoderCount;
    interrupts();

    String DIRECTION = (COUNT>=0)?"Clockwise":"Counterclockwise";
    float  ANGLE     = fmod(abs(COUNT), countsPerRevolution)*360.0/countsPerRevolution;
    int32  REVOLUTION= abs(COUNT)/countsPerRevolution;

    Serial.print("Count: ");  Serial.print(COUNT);
    Serial.print("  Rev: ");  Serial.print(REVOLUTION);
    Serial.print("  Angle: "); Serial.print(ANGLE, 1); Serial.print("deg");
    Serial.print("  Dir: ");  Serial.println(DIRECTION);
}