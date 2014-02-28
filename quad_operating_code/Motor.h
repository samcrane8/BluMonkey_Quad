#ifndef MOTOR_H
#define MOTOR_H

#include "PID.h"

class Motor{
  public:
   Motor(int a_pin, PID* pid);
   void set(float desired, float actual);
  protected:
   int a_pin;
   PID *pid;
}; 

#endif
