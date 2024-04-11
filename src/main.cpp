// side pane: ctrl b
// terminal: ctrl `
// build: ctrl alt b
// upload: ctrl alt u
// serial: ctrl alt s

#include <Arduino.h>
#include <AccelStepper.h>
#include <Adafruit_TSC2046.h>

void setUpPins();
void setUpMotors();
void setUpTouch();

// constants
int maxMotorSpeed = 1000;
int touchCenterX = 2000;
int touchCenterY = 2000;

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

// Touch Controller
const int touch_CS = 20;
const int touch_IRQ = 21; 

AccelStepper mot1(AccelStepper::DRIVER, mot1_stepPin, mot1_dirPin);
AccelStepper mot2(AccelStepper::DRIVER, mot2_stepPin, mot2_dirPin);
Adafruit_TSC2046 touch;

void setup() {
  Serial.begin(9600);
  while(!Serial) {
    delay(10);
  }

  setUpPins();
  setUpMotors();
  setUpTouch();
  Serial.println("Setup Complete");

  // mot1.setSpeed(200);
  // mot2.setSpeed(-200);
}

void loop() {
  // Joystick
  int joyX = analogRead(joy_xPin);
  int joyY = analogRead(joy_yPin);
  
  // Serial.print(joyX);
  // Serial.print(", ");
  // Serial.println(joyY);
  
  // Speed Control
  int speedX = map(joyX, 0, 1023, -maxMotorSpeed, maxMotorSpeed);
  int speedY = map(joyY, 0, 1023, -maxMotorSpeed, maxMotorSpeed);
  mot1.setSpeed(speedX);
  mot2.setSpeed(speedY);

  // Touchscreen
  if (touch.isTouched()) {
    TSPoint ballLoc = touch.getPoint();

    Serial.print(ballLoc.x - touchCenterX);
    Serial.print(", ");
    Serial.println(ballLoc.y - touchCenterY);
  }

  // Motors
  mot1.runSpeed();
  mot2.runSpeed();
  
  delay(50);
}

void setUpPins() {
  // motors
  pinMode(motorEnPin, OUTPUT);

  // joystick
  pinMode(joy_bPin, INPUT); 

  // touch controller
  pinMode(touch_IRQ, INPUT);
}

void setUpMotors() {
  digitalWrite(motorEnPin, LOW);
  mot1.setMaxSpeed(1000);
  mot2.setMaxSpeed(1000);
}

void setUpTouch() {
  int touchResistance = 600; // Resistance across x+ and x-. Used to calculate pressure.
  touch.begin(touch_CS, &SPI, touchResistance);
  // touch.enableInterrupts(true);
}