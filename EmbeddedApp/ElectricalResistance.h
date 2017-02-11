#include "Arduino.h"

class ElectricalResistance {
  private:
    int resistancePin;
    int currentState = LOW;
    
  public:
    ElectricalResistance(int pinNumber);
    void turnOn();  
    void turnOff();
    void partialSet(int percentage);
};
