// build: ctrl alt b
// upload: ctrl alt u

#include <Arduino.h>
#include <AccelStepper.h>

void setUpPins();
void setUpMotors();

// constants
int maxMotorSpeed = 1000;

// Motor Connections
const int motorEnPin = 2;
const int mot1_stepPin = 3;
const int mot1_dirPin = 4; 
const int mot2_stepPin = 5;
const int mot2_dirPin = 6;

// Joystick Connections
const int joy_bPin = 16;
const int joy_xPin = 15;
const int joy_yPin = 14;

AccelStepper mot1(AccelStepper::DRIVER, mot1_stepPin, mot1_dirPin);
AccelStepper mot2(AccelStepper::DRIVER, mot2_stepPin, mot2_dirPin);

void setup() {
  setUpPins();
  setUpMotors();
  Serial.begin(9600);

  // mot1.setSpeed(200);
  // mot2.setSpeed(-200);
}

void loop() {
  int joyX = analogRead(joy_xPin);
  int joyY = analogRead(joy_yPin);
  int speedX = map(joyX, 0, 1023, -maxMotorSpeed, maxMotorSpeed);
  int speedY = map(joyY, 0, 1023, -maxMotorSpeed, maxMotorSpeed);
  mot1.setSpeed(speedX);
  mot2.setSpeed(speedY);
  
  // int speedX 
  // Serial.print(joyX);
  // Serial.print(", ");
  // Serial.println(joyY);

  mot1.runSpeed();
  mot2.runSpeed();
  
  // delay(100);
}

void setUpPins() {
  // motors
  
  pinMode(motorEnPin, OUTPUT);

 // joystick
 pinMode(joy_bPin, INPUT); 
}

void setUpMotors() {
  digitalWrite(motorEnPin, LOW);
  mot1.setMaxSpeed(1000);
  mot2.setMaxSpeed(1000);
}