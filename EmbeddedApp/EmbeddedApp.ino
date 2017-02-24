// Necessary includes in .ino file due to limitation in
// arduino IDE
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <PID_v1.h>

// Applicarion really necessary include files
#include "AppSession.h"

// App definition

#define COLS 20
#define LINES 4

//Global vars
AppDisplay *display;
AppSession *session;

void setup() {
  
  Serial.begin(9600);
  display = new AppDisplay;
  display->splashScreen();
  session = new AppSession(display);
}

void loop() {
  
  //int buttonState = button.getState();
  session->collectData();
  session->refreshStatus();
   //resistance.partialSet(50);
  
  
    
 
}
