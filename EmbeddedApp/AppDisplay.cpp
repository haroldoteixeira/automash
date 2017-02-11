#include "Arduino.h"
#include "AppDisplay.h"

#define COLS 20
#define ROWS 4

AppDisplay::AppDisplay() {
  lcdDisplay = new Display(COLS,ROWS);
  lcdDisplay->setBacklight(HIGH);
}

void AppDisplay::printLine1(String stage, boolean autoStep) {

  lcdDisplay->writeDisplay(stage, 0, 0);
  if (autoStep) {
    lcdDisplay->writeDisplay(" AUT", 16, 0);
  }
}

String AppDisplay::getLineLabel(int line) {
 if (line==2)
  return "SET: ";
 return "CUR: "; 
}

void AppDisplay::printLine2or3(int line, float temp, String time) {
 
  char stringTemp[6];
  int dispLine = line - 1;
  
  lcdDisplay->writeDisplay(getLineLabel(line), 0, dispLine);
  lcdDisplay->writeDisplay(time, 5, dispLine);
  dtostrf(temp, 4, 2, stringTemp);
  lcdDisplay->writeDisplay("/", 12, dispLine);
  lcdDisplay->writeDisplay(stringTemp, 14, dispLine);
  lcdDisplay->writeDisplay("C", 19, dispLine);
}

void AppDisplay::printLine4(String sessionTime, String sessionStatus) {

  lcdDisplay->writeDisplay("SES:", 0, 3);
  lcdDisplay->writeDisplay(sessionTime, 5, 3);
  lcdDisplay->writeDisplay(sessionStatus, 16, 3);
}

void AppDisplay::printMetrics(String stage, boolean autoStep, float curTemp, float stepTemp, String curTime, String stepTime, String sessionTime, String sessionStatus)
{
 
  printLine1(stage, autoStep);
  printLine2or3(2, stepTemp, stepTime);
  printLine2or3(3, curTemp, curTime); 
  printLine4(sessionTime, sessionStatus);
  
}

void AppDisplay::splashScreen() {
   lcdDisplay->clear();
   lcdDisplay->writeDisplay("Automash", 6, 1);
   lcdDisplay->writeDisplay("Ver. 0.1", 6, 2);
   delay(3000); 
   lcdDisplay->clear();
}

