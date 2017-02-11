#include "ElectricalResistance.h"

ElectricalResistance::ElectricalResistance(int pinNumber) {
  
  resistancePin = pinNumber;
  pinMode(resistancePin, OUTPUT);
  digitalWrite(resistancePin, currentState);
}

void ElectricalResistance::turnOn() {
  
  currentState = HIGH;
  digitalWrite(resistancePin, currentState);
  
}

void ElectricalResistance::turnOff() {
  currentState = LOW;
  digitalWrite(resistancePin, currentState);
}

void ElectricalResistance::partialSet(int percentage) {
  currentState = LOW;
  float fraction = percentage / 100.0;
  int dutyCycle = fraction * 255;
  analogWrite(resistancePin, dutyCycle);
}
  
