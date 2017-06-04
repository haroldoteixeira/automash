#include "arduino.h"
#include "TimeCounter.h"
#include "ElectricalResistance.h"
#include "PIDResistanceControl.h"

#define STEP_INI  0
#define STEP_RUN  1
#define STEP_WAIT 2
#define STEP_DONE 3
#define RES_PIN 3
#define KP 90
#define KI 3
#define KD 5

class MashStep {
  
  private:
    TimeCounter _curTime;
    int _progTime;
    float _progTemp;
    String _stepName;
    boolean _auto;
    ElectricalResistance *_resistance;
    PIDResistanceControl *_pidControl;
    int _stepState = STEP_INI;
    void processInitialState(float curTemp);
    void processRunningState(float curTemp);
    void processWaitingState(float curTemp);
    
  public:
    MashStep(int progTime, float progTemp, String stepName, boolean autoStep);
    ~MashStep();
    void start();
    int updateState(float curTemp);
    String getStepName();
    String getCurTime();
    String getProgTime();
    float getProgTemp();
    boolean getAutoFlag();
    
};

