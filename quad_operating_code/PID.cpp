#include "PID.h"

PID::PID(float K_p,float K_i, float K_d){
  this->K_p = K_p;
  this->K_i = K_i;
  this->K_d = K_d;
  lastError = 0;
}

float PID::get(float desired, float actual){
 float error = desired-actual;
 return getP(error) + getD(error);
}

float PID::getP(float error){
  return error*K_p;
}

float PID::getD(float error){
  float der = error-lastError;
  der *= K_d;
  lastError = error;
  return der;
}
