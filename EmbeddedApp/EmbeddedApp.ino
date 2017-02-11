// Necessary includes in .ino file due to limitation in
// arduino IDE
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>


// Applicarion really necessary include files
#include "ElectricalResistance.h"
#include "Buzzer.h"
#include "AppSession.h"

// App definition

#define RES_PIN 3
#define BUZZER_PIN 4
#define COLS 20
#define LINES 4

//Global vars
ElectricalResistance resistance(RES_PIN);
Buzzer buzzer(BUZZER_PIN);
AppDisplay *display;
AppSession *session;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Rodou");
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
