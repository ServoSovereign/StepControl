#pragma once
#include <Arduino.h>

typedef uint8_t uint8;
typedef uint16_t uint16;

extern const uint8 stepPinX;
extern const uint8 stepPinY; 
extern const uint8 dirrectionPinX;  
extern const uint8 dirrectionPinY;  
extern const uint8 enablePin;
extern const uint16 baudRate;       
extern const float STEPS_PER_CM_X;  
extern const float STEPS_PER_CM_Y; 

void initDriver();