#include "arduino.h"
#include "Button.h"

Button::Button(int pin) {
  pinButton = pin;
  pinMode(pinButton, INPUT);
}

int Button::getState() {
  return digitalRead(pinButton);
}

