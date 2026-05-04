#include "Config.h"

typedef uint8_t uint8;
typedef uint16_t uint16;

const uint8 stepPinX        =2;
const uint8 stepPinY        =3;
const uint8 dirrectionPinX  =5;
const uint8 dirrectionPinY  =6;
const uint8 enablePin       =8;
const uint16 baudRate       =9600;

const float STEPS_PER_CM_X  =780.0;
const float STEPS_PER_CM_Y  =780.0;

void initDriver(){
    Serial.begin(baudRate);
    
    pinMode(stepPinX, OUTPUT);
    pinMode(stepPinY, OUTPUT);
    pinMode(dirrectionPinX, OUTPUT);
    pinMode(dirrectionPinY, OUTPUT);
    pinMode(enablePin, OUTPUT);

    digitalWrite(enablePin, LOW);

    Serial.println("Driver OK");
}