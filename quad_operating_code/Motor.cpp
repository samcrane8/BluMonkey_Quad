#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int a_pin, PID *pid){
 this->a_pin = a_pin; 
 this->pid = pid;
}

void Motor::set(float desired, float actual){
  int val = map(pid->get(desired,actual),0,1,0,255);
  analogWrite(a_pin,val);
}

