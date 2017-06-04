#include "TemperatureSensor.h"


TemperatureSensor::TemperatureSensor (uint8_t busPin, int sensorResolution) {
  
    oneWireControl = new OneWire(busPin);
    sensorSet = new DallasTemperature(oneWireControl);
    sensorSet->begin();
    sensorSet->getAddress(tempSensor, 0);
}
  
  
void TemperatureSensor::setResolution (int sensorResolution) {
    sensorSet->setResolution(tempSensor, 10);
}

float TemperatureSensor::getTemperature() {
    sensorSet->requestTemperatures();
    float retTemp = sensorSet->getTempC(tempSensor);    
    return retTemp + sensorError;
}

