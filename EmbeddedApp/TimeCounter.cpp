#include "TimeCounter.h"

void TimeCounter::start() {
 
 _counterValue =0;
 _baseTime = now();
 
}

void TimeCounter::update() {

  _counterValue = now() - _baseTime;

}

String TimeCounter::getTimeCount() {
  
  char returnMessage[10];
  sprintf(returnMessage, "%03d:%02d", (_counterValue/60), (_counterValue%60));
  return returnMessage;
}

