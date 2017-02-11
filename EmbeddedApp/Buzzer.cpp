#include "Arduino.h"
#include "Buzzer.h"

Buzzer::Buzzer(int pin) {
  pinBuzzer = pin;
  pinMode(pinBuzzer, OUTPUT);
}

void Buzzer::play(int frequency) {
    tone(pinBuzzer, frequency);
}

void Buzzer::mute() {
  noTone(pinBuzzer);
}

