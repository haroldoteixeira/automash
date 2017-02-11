#include <Time.h>
#include "arduino.h"

class TimeCounter {
  
  private:
    int _counterValue = 0;
    int _baseTime = 0;
        
  public:
    void start();
    void update();
    String getTimeCount();
    
};
