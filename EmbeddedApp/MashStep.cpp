#include "MashStep.h"

MashStep::MashStep(int progTime, float progTemp, String stepName, boolean autoStep) {
   _auto = autoStep;
   _progTime = progTime;
   _progTemp = progTemp;
   _stepName = stepName;
   _resistance = new ElectricalResistance(RES_PIN);
   
}

void MashStep::start() {

  _stepState = STEP_INI;
}

int MashStep::updateState(float curTemp) {

  
  switch (_stepState) {
    case STEP_INI:
      processInitialState(curTemp);
      break;
    case STEP_RUN:
      processRunningState(curTemp);
      break;
    case STEP_WAIT:
      //processWaitingStep();
      break;
    default:
      break;
  }
  Serial.println("Estado: ");
  Serial.println(_stepState);
  return _stepState;
}

void MashStep::processInitialState(float curTemp) {
  if (curTemp < _progTemp) {
    _resistance->turnOn();
  } else {
    _curTime.start();
    _resistance->turnOff();
    _stepState = STEP_RUN;
  } 
}

void MashStep::processRunningState(float curTemp) {
  _curTime.update();
  Serial.print("Temp: ");
  Serial.println(_curTime.getMinutesCount());
  if (_curTime.getMinutesCount() < _progTime) {
    //Lógica acionamento resistencia
    _stepState = STEP_RUN;
  } else {
    if (_auto) {
      _stepState = STEP_DONE;
    } else {
      _stepState = STEP_WAIT;  
    }
  }
}

String MashStep::getStepName() {
 return _stepName; 
}

String MashStep::getProgTime() {
  char returnMsg[10];
  sprintf(returnMsg, "%03d:00", _progTime);
  return returnMsg;
}

String MashStep::getCurTime() {
 return _curTime.getTimeCount();
}

float MashStep::getProgTemp() {
  return _progTemp;
}

boolean MashStep::getAutoFlag() {
  return _auto;
}
    
