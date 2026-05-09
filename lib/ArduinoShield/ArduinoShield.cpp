#include "ArduinoShield.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

static const uint8 stepPinX =2;
static const uint8 stepPinY =3;
static const uint8 stepPinZ =4;
//static const uint8 stepPinA =12;

static const uint8 dirrectionPinX =5;
static const uint8 dirrectionPinY =6;
static const uint8 dirrectionPinZ =7;
//static const uint8 dirrectionPinA =13;

static const uint8  enablePin   =8;
static const uint16 motorSpeed  =1000;
static const uint32 baudRate    =115200;

static const int STEPS_PER_CM=800;
static const float STEPS_PER_CM_X =780.0;
static const float STEPS_PER_CM_Y =780.0;
static const float STEPS_PER_CM_Z =780.0;
//static const float STEPS_PER_CM_A =780.0;

static float targetDistanceX;
static float targetDistanceY;
static float targetDistanceZ;
//static float targetDistanceA;

float numberOfStepsX;
float numberOfStepsY;
float numberOfStepsZ;
//float numberOfStepsA;

float moveDistanceX;
float moveDistanceY;
float moveDistanceZ;
//float moveDistanceA;

uint32 currentX=0;
uint32 currentY=0;
uint32 currentZ=0;
//uint32 currentA=0;

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

String getStringSerial(){
  String received = "";
  while(Serial.available() == 0)
    delay(50);
  while (Serial.available() > 0){
        char c = Serial.read();
        if (c == '\n' || c == '\r') break;
        received += c;
  }
  return received;
}

void getDistance(){
  Serial.println("Input for X (cm): ");
  targetDistanceX = getStringSerial().toFloat();
  Serial.println("Input for Y (cm): ");
  targetDistanceY = getStringSerial().toFloat();
}

void convertToSteps(){
  numberOfStepsX = round(targetDistanceX * STEPS_PER_CM_X);
  numberOfStepsY = round(targetDistanceY * STEPS_PER_CM_Y);
}

void distanceToMove(){
  moveDistanceX = numberOfStepsX - currentX;
  moveDistanceY = numberOfStepsY - currentY;
}

void setDirection(){
  moveDistanceX > 0 ? digitalWrite(dirrectionPinX, HIGH) : digitalWrite(dirrectionPinX, LOW);
  moveDistanceY > 0 ? digitalWrite(dirrectionPinY, HIGH) : digitalWrite(dirrectionPinY, LOW);
}

void runMotors(float moveDistanceX, float moveDistance) {
  float stepsX = abs(moveDistanceX);
  float stepsY = abs(moveDistanceY);
  float i = 0;

  while (i < stepsX || i < stepsY) {
    if (i < stepsX) digitalWrite(stepPinX, HIGH);
    if (i < stepsY) digitalWrite(stepPinY, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(stepPinX, LOW);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(motorSpeed);
    i++;
  }
}

void renewCoord(){
  currentX = (uint32)numberOfStepsX;
  currentY = (uint32)numberOfStepsY;
  Serial.println("Done moving");
}

void resetMotor(){
  moveDistanceX=0;
  moveDistanceY=0;
  moveDistanceZ=0;
//  moveDistanceA=0;
}

void serialMotorMode(){
  getDistance();
  convertToSteps();
  distanceToMove();
  setDirection();
  runMotors(moveDistanceX, moveDistanceY);
  renewCoord();
}

void testChannelDriver(){
  Serial.println("Distance of travel (cm): ");
    uint32  Distance=getStringSerial().toInt();
  Serial.println("Dirrection: 1)Forward/2) Backward");
    uint8  Dirrection=getStringSerial().toInt();
  //Fix channel here
  Dirrection==1?digitalWrite(dirrectionPinY, HIGH):digitalWrite(dirrectionPinY, LOW);

  uint32 numberOfSteps =  Distance*STEPS_PER_CM;
  for(uint32 i=0; i<numberOfSteps; i++){
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(motorSpeed);
  }
}