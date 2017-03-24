#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Time.h>

#include "Button.h"
#include "ElectricalResistance.h"
#include "TemperatureSensor.h"
#include "TimeCounter.h"

#define TEMP_SENSOR_PIN 2
#define BUTTON_PIN 5
#define TEMP_SENSOR_RES 10
#define COLS 20
#define ROWS 4
#define RES_PIN 3

TemperatureSensor temperatureSensor(TEMP_SENSOR_PIN, TEMP_SENSOR_RES);
Button button(BUTTON_PIN);
ElectricalResistance resistance(RES_PIN);
String stepName[] = { "STEP1", "STEP2", "STEP3", "STEP4", "STEP5", "STEP6"};
double setPoint[] = {40, 50, 60, 65, 68, 76};
int currentStep = 0;
int steps = 6;
TimeCounter counter;

void setup() {
  
  Serial.begin(9600);
  counter.start();
}

void printData(float temp, String stepName) {

  char strTemp[6];
  dtostrf(temp, 4, 2, strTemp);
  Serial.print(stepName);
  Serial.print(";");
  Serial.print(counter.getTimeCount());
  Serial.print(";");
  Serial.println(strTemp);
  
}

void loop() {
  while (currentStep < steps) {
    counter.update();
    float temp = temperatureSensor.getTemperature();
    printData(temp, stepName[currentStep]);
    if (temp < setPoint[currentStep]) {
      resistance.turnOn();
    } else {
      resistance.turnOff();
      if (button.getState() == HIGH) {
        currentStep++;
        counter.start();
      }  
    }
  }
}
