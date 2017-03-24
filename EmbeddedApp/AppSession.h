#include "TemperatureSensor.h"
#include "AppDisplay.h"
#include "Button.h"
#include "Buzzer.h"
#include "MashStep.h"

// State definition constants
#define INITIAL 0
#define HEATING 1
#define RUNNING 2
#define WAITING 3
#define DONE 4

#define TEMP_SENSOR_PIN 2
#define TEMP_SENSOR_RES 10
#define BUTTON_PIN 5
#define BUZZER_PIN 4

class AppSession {
 
  private:
    TemperatureSensor *_tempSensor;
    AppDisplay *_display;
    Button *_button;
    Buzzer *_buzzer;
    MashStep *_mashStep[9];
    int _curStep = 0;
    int _stepCount;
    
    float _curTemperature;
    TimeCounter _sessionTimer;
    int _sessionState = INITIAL;
    
    float collectTemp();
    int collectSessionTime();
    int updateState();
    void processInitialState();
    void processHeatingState();
    void processRunningState();
    void processWait();
    void startSession();
    void nextStep();
    void initializeSessionList();
    
    
  public:
    AppSession(AppDisplay *display);
    void collectData();
    void refreshStatus();
    void logData();
    
};
