#include "AppSession.h"


void AppSession::initializeSessionList(){
   
   _mashStep[0] = new MashStep(10, 52, "PROTEIN REST", FALSE);
   _mashStep[1] = new MashStep(60, 64, "SACARIFICATION", FALSE);
   _mashStep[2] = new MashStep(15, 77, "MASH OUT", FALSE);
   _stepCount = 3; 
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
   if ((_sessionState != INITIAL) && (_sessionState != DONE)){
     _sessionTimer.update();
   }
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
     break;
    default:
     processRunningState();
     break;
  }
}

void AppSession::processInitialState() {
    int buttonVal = _button->getState();
    /*Serial.print("BotÃ£o: ");
    Serial.println(buttonVal);*/
    if (buttonVal == HIGH) {    
      startSession(); 
  } 
    
}

void AppSession::startSession() {
  _sessionTimer.start();
  _sessionState = HEATING;
  initializeSessionList();
  _display->clearScreen();
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
    
    int buttonVal = _button->getState();
    /*Serial.print("BotÃ£o: ");
    Serial.println(buttonVal);*/
    _sessionState = WAITING;
    if (buttonVal == HIGH) {
      nextStep();
    }
}


void AppSession::refreshStatus() {
  String stateLabel[5] = {" INI", "HEAT", " RUN", "WAIT", "DONE"};
  if (_sessionState != INITIAL) {
    float progTemp = 0.0;
    String progTime = "000:00";
    String curTime = "000:00";
    if (_sessionState != DONE) {
      progTemp = _mashStep[_curStep]->getProgTemp();
      progTime = _mashStep[_curStep]->getProgTime();
      curTime = _mashStep[_curStep]->getCurTime();
      _display->printMetrics(_mashStep[_curStep]->getStepName(), _mashStep[_curStep]->getAutoFlag(), _curTemperature, progTemp, curTime, progTime, _sessionTimer.getTimeCount(), stateLabel[_sessionState]);
    } else {
      _display->printMetrics("MASH COMPLETE", "   ", _curTemperature, 0.0, "000:00", "000:00", _sessionTimer.getTimeCount(), stateLabel[_sessionState]); 
    }
  } else {
    _display->startScreen();
  }

}

void AppSession::logData() {

  char stringTemp[6];
  
  dtostrf(_curTemperature, 4, 2, stringTemp);
  Serial.print(_sessionTimer.getTimeCount());
  Serial.print(";");
  Serial.print((_curStep+1));
  Serial.print(";");
  Serial.println(stringTemp);
}


