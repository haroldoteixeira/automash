#include "TemperatureSensor.h"
#include "AppDisplay.h"
#include "TimeCounter.h"
#include "Button.h"

// State definition constants
#define INITIAL 0
#define HEATING 1
#define RUNNING 2
#define WAITING 3
#define DONE 4

#define TEMP_SENSOR_PIN 2
#define TEMP_SENSOR_RES 10
#define BUTTON_PIN 5

class AppSession {
 
  private:
    TemperatureSensor *_tempSensor;
    AppDisplay *_display;
    Button *_button;

    
    float _curTemperature;
    TimeCounter _sessionTimer;
    int _sessionState = INITIAL;
    
    float collectTemp();
    int collectSessionTime();
    int updateState();
    void processInitialState();
    void startSession();
    
  public:
    AppSession(AppDisplay *display);
    void collectData();
    void refreshStatus();
   
    
};
