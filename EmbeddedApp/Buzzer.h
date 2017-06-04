#include "arduino.h"

class Buzzer {
  
  private:
  
    int pinBuzzer;
    
  public:
  
  Buzzer(int pin);
  void play(int frequency);
  void mute();
};

