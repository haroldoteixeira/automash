#include "Display.h"

Display::Display(int qtColumns, int qtLines) {
  lcd = new LiquidCrystal_I2C(0x27,2,1,0,4,5,6,7,3, POSITIVE);
  lcd->begin(qtColumns, qtLines);
}

void Display::setBacklight(int state) {
  lcd->setBacklight(state);
}

void Display::writeDisplay(String text, int X, int Y) {
  lcd->setCursor(X, Y);
  lcd->print(text);
}

void Display::clear() {
  lcd->clear();
}


