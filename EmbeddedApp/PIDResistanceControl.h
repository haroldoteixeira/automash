#include <PID_v1.h>
#include <arduino.h>
#include "IResistanceControl.h"

class PIDResistanceControl : public IResistanceControl {
  
  public:
  PIDResistanceControl(double setPoint);
  void setParameters(int Kp, int Ki, int Kd);
  double computeOutput(double input);
 
  private:
    double _setPoint;
    double _input, _output;
    PID *_controller;
    
};
