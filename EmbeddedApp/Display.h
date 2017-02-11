#include "arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Display {
 
  private:
    LiquidCrystal_I2C *lcd;
  
  public:
   Display(int qtLines, int qtColumns);
   void setBacklight(int state);
   void writeDisplay(String text, int X, int Y);
   void clear();
};
    
