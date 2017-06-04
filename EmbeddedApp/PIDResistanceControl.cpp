#include "PIDResistanceControl.h"

PIDResistanceControl::PIDResistanceControl (double setPoint) {
  
  _setPoint = setPoint;
  _controller = new PID(&_input, &_output, &_setPoint, 1, 1, 1, DIRECT);
  _controller->SetMode(AUTOMATIC);
  _controller->SetOutputLimits(0, 100);
  
}

void PIDResistanceControl::setParameters(int Kp, int Ki, int Kd) {
   _controller->SetTunings(Kp, Ki, Kd); 
}

double PIDResistanceControl::computeOutput(double input) {
  
    _input = input;
    _controller->Compute();
    Serial.println("----------------");
    Serial.println(_setPoint);
    Serial.println(_output);
    return _output;   
}

