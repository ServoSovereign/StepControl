#include <Arduino.h>
#include <String.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

const uint8 stepPinX        =2;
const uint8 stepPinY        =3;
const uint8 dirrectionPinX  =5;
const uint8 dirrectionPinY  =6;
const uint8 enablePin       =8;
const uint32 baudRate       =115200;
const float STEPS_PER_CM_X  =780.0;
const float STEPS_PER_CM_Y  =780.0;

uint32 currentX=0;
uint32 currentY=0;

String receiveString();
void homeMotors();
void runMotors(float moveDistanceX, float moveDistanceY);

void setup() {
  Serial.begin(baudRate);

  pinMode(stepPinX, OUTPUT);
  pinMode(stepPinY, OUTPUT);
  pinMode(dirrectionPinX, OUTPUT);
  pinMode(dirrectionPinY, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  digitalWrite(enablePin, LOW);
  Serial.println("Driver OK");
  homeMotors();
}

void loop() {
  Serial.println("Input for X (cm): ");
  float targetDistanceX = receiveString().toFloat();
  Serial.println("Input for Y (cm): ");
  float targetDistanceY = receiveString().toFloat();

  float targetStepsX = round(targetDistanceX * STEPS_PER_CM_X);
  float targetStepsY = round(targetDistanceY * STEPS_PER_CM_Y);

  float moveDistanceX = targetStepsX - currentX;
  float moveDistanceY = targetStepsY - currentY;

  moveDistanceX > 0 ? digitalWrite(dirrectionPinX, HIGH) : digitalWrite(dirrectionPinX, LOW);
  moveDistanceY > 0 ? digitalWrite(dirrectionPinY, HIGH) : digitalWrite(dirrectionPinY, LOW);

  runMotors(moveDistanceX, moveDistanceY);

  currentX = (uint32)targetStepsX;
  currentY = (uint32)targetStepsY;

  Serial.println("Done moving");
  delay(1000);
}

void homeMotors() {
  Serial.println("Homing motors...");

  // Set direction toward origin (LOW = toward 0)
  digitalWrite(dirrectionPinX, LOW);
  digitalWrite(dirrectionPinY, LOW);

  // Step back by however many steps we are from origin
  for (uint32 i = 0; i < currentX || i < currentY; i++) {
    if (i < currentX) digitalWrite(stepPinX, HIGH);
    if (i < currentY) digitalWrite(stepPinY, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinX, LOW);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(1000);
  }

  currentX = 0;
  currentY = 0;
  Serial.println("Homing complete.");
}

String receiveString() {
  String received = "";
  while (Serial.available() == 0); // wait for first byte

  delay(50); // let full string arrive in buffer
  
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') break;
    received += c;
  }
  return received;
}

void runMotors(float moveDistanceX, float moveDistanceY) {
  float stepsX = abs(moveDistanceX);
  float stepsY = abs(moveDistanceY);
  float i = 0;

  while (i < stepsX || i < stepsY) {
    if (i < stepsX) digitalWrite(stepPinX, HIGH);
    if (i < stepsY) digitalWrite(stepPinY, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinX, LOW);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(500);
    i++;
  }
}