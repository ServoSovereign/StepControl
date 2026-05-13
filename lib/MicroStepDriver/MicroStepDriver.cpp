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
static const uint16 pulsesPerRevMotor   = 1600;
static const uint16 countsPerRevEncoder = 400;
static const uint32 baudRate    = 115200;
volatile int32 encoderCount     = 0;

void initDriver(){
    Serial.begin(baudRate);
    delay(1000);
    
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);

    pinMode(enablePin,   OUTPUT);
    pinMode(directionPin,OUTPUT);
    pinMode(pulsePin,    OUTPUT);

    digitalWrite(enablePin, LOW);
    Serial.println("Driver OK"); 
}

void initEncoder(){
    attachInterrupt(
        digitalPinToInterrupt(encoderPinA), 
        readEncoder, 
        CHANGE
    );
    attachInterrupt(
        digitalPinToInterrupt(encoderPinB),
        readEncoder,
        CHANGE
    );
    Serial.println("Encoder OK");
}

void setDirMotor(int Direction){
    if(Direction==0)
        digitalWrite(directionPin, LOW);
    else
        digitalWrite(directionPin, HIGH);
}

uint32 getPulses(uint32 numberOfRevolution){
    return(numberOfRevolution*pulsesPerRevMotor);
}

void readEncoder() {
    static uint8 lastState=(
        digitalRead(encoderPinA)<<1|
        digitalRead(encoderPinB)
    ); 

    bool A = digitalRead(encoderPinA);
    bool B = digitalRead(encoderPinB);

    uint8 currentState= (A<<1)|B;
    uint8 nextState   = (lastState<<2)|currentState;

    switch(nextState){
        //Clockwise
        case 0b0001:
        case 0b0111:
        case 0b1110:
        case 0b1000:
            encoderCount++;
            break;
        //Counter-clockwise
        case 0b0010:
        case 0b1011:
        case 0b1101:
        case 0b0100:
            encoderCount--;
            break;
    }
    lastState=currentState;
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
    int32 COUNT = encoderCount/4;
    interrupts();

    String DIRECTION = (COUNT>=0)?"Clockwise":"Counterclockwise";
    float  ANGLE     = fmod(abs(COUNT), countsPerRevEncoder)*360.0/countsPerRevEncoder;
    int32  REVOLUTION= abs(COUNT)/countsPerRevEncoder;

    Serial.print("Count: ");  Serial.print(COUNT);
    Serial.print("  Rev: ");  Serial.print(REVOLUTION);
    Serial.print("  Angle: "); Serial.print(ANGLE, 1); Serial.print("deg");
    Serial.print("  Dir: ");  Serial.println(DIRECTION);
}