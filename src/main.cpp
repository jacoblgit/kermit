// build: ctrl alt b
// upload: ctrl alt u

#include <Arduino.h>
#include <AccelStepper.h>

// Motor Connections
const int motorEnPin = 2;
// Motor 1 
const int mot1_stepPin = 3;
const int mot1_dirPin = 4; 
// Motor 2
const int mot2_stepPin = 5;
const int mot2_dirPin = 6; 

AccelStepper mot1(AccelStepper::DRIVER, mot1_stepPin, mot1_dirPin);
AccelStepper mot2(AccelStepper::DRIVER, mot2_stepPin, mot2_dirPin);

void setup() {
  pinMode(motorEnPin, OUTPUT);
  digitalWrite(motorEnPin, LOW);
  mot1.setMaxSpeed(1000);
  mot2.setMaxSpeed(1000);
  mot1.setSpeed(200);
  mot2.setSpeed(200);
}

void loop() {
  mot1.runSpeed();
  mot2.runSpeed();
}