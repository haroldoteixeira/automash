#include "AppSession.h"


AppSession::AppSession(AppDisplay *display) {
  _display = display;
  _tempSensor = new TemperatureSensor(TEMP_SENSOR_PIN, TEMP_SENSOR_RES);
  _button = new Button(BUTTON_PIN);
}

float AppSession::collectTemp() {
  
  return _tempSensor->getTemperature();

}

void AppSession::collectData() {
 
   _curTemperature = collectTemp();
   if (_sessionState != INITIAL)
     _sessionTimer.update();
   updateState();
}

int AppSession::updateState() {
 
  
  switch(_sessionState)
  {
    case INITIAL:
     processInitialState();
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
}

void AppSession::refreshStatus() {
  String stateLabel[5] = {" INI", "HEAT", " RUN", "WAIT", "DONE"};
  
  _display->printMetrics("1-SACARIFICACAO", true, _curTemperature, 99.9, "000:00", "001:00", _sessionTimer.getTimeCount(), stateLabel[_sessionState]); 
  
}
