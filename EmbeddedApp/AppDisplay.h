#include "Display.h"

class AppDisplay {
  
  private:
    Display *lcdDisplay;
    void printLine1(String stage, boolean auto);
    void printLine2or3(int line, float stepTemp, String stepTime);
    void printLine4(String sessionTime, String sessionStatus);
    String getLineLabel(int line);
    
  public:
    AppDisplay();
    void printMetrics(String stage, boolean auto, float curTemp, float stepTemp, String curTime, String stepTime, String sessionTime, String sessionStatus);
    void splashScreen();
    void startScreen();
   
};

