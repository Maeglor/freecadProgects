#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#pragma once
#include <Arduino.h>


#define SPEED_LIMIT 800

class StepperMotor {
private:
  int stepperPin, directioPin, microStep1Pin;

  int targetPosition = 0,
      currentPosition = 0,
      currentSpin = 0;
  int targetMicros = 0;      
  bool stepperValue = false;


public:
  StepperMotor(int stepperPin, int directioPin, int microStep1Pin) {
    this->directioPin = directioPin;
    this->stepperPin = stepperPin;
    this->microStep1Pin = microStep1Pin;



    pinMode(directioPin, OUTPUT);
    pinMode(stepperPin, OUTPUT);
    // pinMode(microStep1Pin, OUTPUT);
  };

  void setTargetPosition(int targetPosition) {
    this->targetPosition = targetPosition;
  };

  void setTargetPosition(double targetPosition) {
    this->targetPosition = (int)targetPosition;
  };

  void setTargetPosition(float targetPosition) {
    this->targetPosition = (int)targetPosition;
  };

  void reset(){
    targetPosition = 0;
    currentPosition = 0;
  };

  void process();
};




void StepperMotor::process() {
  // while (targetPosition != currentPosition) {
  // step(targetPosition - currentPosition);
  int distance = targetPosition - currentPosition;
  if (distance == 0)
    return;

  int absdistance = abs(distance);
  int spin = distance / absdistance;

  if (spin != currentSpin) {
    digitalWrite(directioPin, (spin > 0) ? HIGH : LOW);
    currentSpin = spin;
  }
 
  while(targetMicros>micros());
  targetMicros = micros()+SPEED_LIMIT;
  digitalWrite(stepperPin, HIGH);

  currentPosition += currentSpin;
  while(targetMicros>micros());
  targetMicros = micros()+SPEED_LIMIT;
  digitalWrite(stepperPin, LOW);
}