#include "ArduinoShield.h"

typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

static const uint8 pulsePinX =2;
static const uint8 pulsePinY =3;
static const uint8 pulsePinZ =4;

static const uint8 dirrectionPinX =5;
static const uint8 dirrectionPinY =6;
static const uint8 dirrectionPinZ =7;

static const uint8  enablePin   =8;
static const uint16 stepDelay   =300;
static const uint32 baudRate    =115200;

void initDriver(){
  Serial.begin(baudRate);

  pinMode(pulsePinX, OUTPUT);
  pinMode(pulsePinY, OUTPUT);
  pinMode(pulsePinZ, OUTPUT);

  pinMode(dirrectionPinX, OUTPUT);
  pinMode(dirrectionPinY, OUTPUT);
  pinMode(dirrectionPinZ, OUTPUT);

  pinMode(enablePin, OUTPUT);
  
  digitalWrite(enablePin, LOW);
  Serial.println("Driver OK");
}

void runMotorChannelX(int32 numberOfPulses){
  for(int i=0; i<numberOfPulses; i++){
    digitalWrite(pulsePinX, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(pulsePinX, LOW);
    delayMicroseconds(stepDelay);
  }
}

void runMotorChannelY(int32 numberOfPulses){
  for(int i=0; i<numberOfPulses; i++){
    digitalWrite(pulsePinY, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(pulsePinY, LOW);
    delayMicroseconds(stepDelay);
  }
}

void runMotorChannelZ(int32 numberOfPulses){
  for(int i=0; i<numberOfPulses; i++){
    digitalWrite(pulsePinZ, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(pulsePinZ, LOW);
    delayMicroseconds(stepDelay);
  }
}


void setDirectionChannelX(bool Bit){
  digitalWrite(dirrectionPinX, Bit);
}

void setDirectionChannelY(bool Bit){
  digitalWrite(dirrectionPinY, Bit);
}

void setDirectionChannelZ(bool Bit){
  digitalWrite(dirrectionPinZ, Bit);
}

void testDirectionChannelX(){
  digitalWrite(dirrectionPinX, HIGH);
}

void testDirectionChannelY(){
  digitalWrite(dirrectionPinY, HIGH);
}

void testDirectionChannelZ(){
  digitalWrite(dirrectionPinZ, HIGH);
}