#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor {
  
  private:
      OneWire *oneWireControl;
      DallasTemperature *sensorSet;
      DeviceAddress tempSensor;
      const int sensorError = 2;
    
   public:
      TemperatureSensor (uint8_t busPin, int sensorResolution);
      void setResolution (int sensorResolution);
      float getTemperature();
};
