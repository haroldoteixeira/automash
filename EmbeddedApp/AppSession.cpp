#include "AppSession.h"


void AppSession::initializeSessionList(){
   
   _mashStep[0] = new MashStep(1, 28, "ACID REST", FALSE);
   _mashStep[1] = new MashStep(1, 33, "PROTEIN REST", TRUE);
   _stepCount = 2; 
}

AppSession::AppSession(AppDisplay *display) {
  _display = display;
  _tempSensor = new TemperatureSensor(TEMP_SENSOR_PIN, TEMP_SENSOR_RES);
  _button = new Button(BUTTON_PIN);
  _buzzer = new Buzzer(BUZZER_PIN);
}

float AppSession::collectTemp() {
  
  return _tempSensor->getTemperature();

}

void AppSession::collectData() {
 
   _curTemperature = collectTemp();
   if ((_sessionState != INITIAL) && (_sessionState != DONE))
     _sessionTimer.update();
   updateState();
}

int AppSession::updateState() {
 
  
  switch(_sessionState)
  {
    case INITIAL:
     processInitialState();
     break;
    case HEATING:
     processHeatingState();
    case RUNNING:
     processRunningState();
     break;
    default:
     break;
  }
}

void AppSession::processInitialState() {
  if (_button->getState() == LOW) {
    startSession(); 
  } 
    
}

void AppSession::startSession() {
  _sessionTimer.start();
  _sessionState = HEATING;
  initializeSessionList();
  _mashStep[_curStep]->start();
}

void AppSession::processHeatingState() {
  if ((_mashStep[_curStep]->updateState(_curTemperature)) != STEP_INI) {
    _sessionState = RUNNING;
  }
}

void AppSession::processRunningState()
{
   switch(_mashStep[_curStep]->updateState(_curTemperature)) {
     case STEP_RUN:
       break;
     case STEP_DONE:
       nextStep();
       break;
     case STEP_WAIT:
       processWait();
       break;
     default:
       break;
   }
}

void AppSession::nextStep() {
    _curStep++;
    if (_curStep < _stepCount) {
       _sessionState = HEATING;
       _mashStep[_curStep]->start(); 
    }
    else {
      _sessionState = DONE;
    }
}

void AppSession::processWait() {
    
    if (_button->getState() == LOW) {
      nextStep();
    }
}


void AppSession::refreshStatus() {
  String stateLabel[5] = {" INI", "HEAT", " RUN", "WAIT", "DONE"};
  if (_sessionState != INITIAL) {
    float progTemp = 0.0;
    String progTime = "000:00";
    if (_sessionState != DONE) {
      progTemp = _mashStep[_curStep]->getProgTemp();
      progTime = _mashStep[_curStep]->getProgTime();
    }
    _display->printMetrics(_mashStep[_curStep]->getStepName(), _mashStep[_curStep]->getAutoFlag(), _curTemperature, progTemp, _mashStep[_curStep]->getCurTime(), progTime, _sessionTimer.getTimeCount(), stateLabel[_sessionState]); 
  } else {
    _display->startScreen();
  }
}
