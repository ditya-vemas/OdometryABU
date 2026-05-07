#include "OdometryABU.h"
#include "CMPS14.h"
#include <RotaryEncoder.h>

const int ENC_1A = 28, ENC_1B = 29;
const int ENC_2A = 30, ENC_2B = 31;
const int ENC_3A = 32, ENC_3B = 33;

Odometry odom(100, 2400, 2400, 2400);
CMPS14 compass;
RotaryEncoder *encoderA = nullptr, *encoderB = nullptr, *encoderC = nullptr;

float posX = 0;
float posY = 0;
float heading = 0;

long posA = 0;
long posB = 0;
long posC = 0;

void setup() {
  Serial.begin(115200);

  initializeEncoders();

  compass.begin();
  compass.resetHeading();
}

void loop() {
  odometryRoutine();

  Serial.print("X: ");
  Serial.print(posX);
  Serial.print(" | Y: ");
  Serial.print(posY);
  Serial.print(" | heading: ");
  Serial.println(heading);

  delay(10); 
}

// 🖥️ INTERRUPT SERVICE ROUTINES (ISR)
void handleEncoderA() {
  encoderA->tick();
}
void handleEncoderB() {
  encoderB->tick();
}
void handleEncoderC() {
  encoderC->tick();
}

void initializeEncoders() {
  encoderA = new RotaryEncoder(ENC_1A, ENC_1B, RotaryEncoder::LatchMode::TWO03);
  encoderB = new RotaryEncoder(ENC_2A, ENC_2B, RotaryEncoder::LatchMode::TWO03);
  encoderC = new RotaryEncoder(ENC_3A, ENC_3B, RotaryEncoder::LatchMode::TWO03);

  attachInterrupt(digitalPinToInterrupt(ENC_1A), handleEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_1B), handleEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_2A), handleEncoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_2B), handleEncoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_3A), handleEncoderC, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_3B), handleEncoderC, CHANGE);
}

void odometryRoutine() {
  heading = compass.getHeading();
  posA = encoderA->getPosition();
  posB = encoderB->getPosition();
  posC = encoderC->getPosition();

  odom.readCoordinate(posA, posB, posC, heading);

  posX = odom.posX;
  posY = odom.posY;
}