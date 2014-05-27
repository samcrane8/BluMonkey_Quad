#include "FilterKalman.h"

FilterKalman::FilterKalman(){
  Q_angle = 0.001;
  Q_bias = 0.003;
  R_measure = 0.03;
  
  angle = 0;
  bias = 0;
  
  P[0][0] = 0;
  P[0][1] = 0;
  P[1][0] = 0;
  P[1][1] = 0;
}

double FilterKalman::getAngle(double newAngle, double newRate, double dt){
   
  rate = newRate - bias;
  angle += dt * rate;
  
  //update estimation error covariance - Project the error covariance ahead
  P[0][0] += dt*(dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt* P[1][1];
  P[1][0] -= dt*P[1][1];
  P[1][1] += Q_bias * dt;
  
  // Discrete Kalman filter measurement
  S = P[0][0] + R_measure;
  K[0] = P[0][0] / S;
  K[1] = P[1][0] / S;
  
  //calculate the angle and bias
  y = newAngle - angle;
  angle += K[0] * y;
  bias += K[1] * y;
  
  P[0][0] -= K[0] * P[0][0];
  P[0][1] -= K[0] * P[0][1];
  P[1][0] -= K[1] * P[0][0];
  P[1][1] -= K[1] * P[0][1];
  
  return angle;
}

void FilterKalman::setAngle(double newAngle) { 
  angle = newAngle; 
};

double FilterKalman::getRate() { return rate; }

void FilterKalman::setQangle(double newQ_angle){
  
}

void FilterKalman::setQbias(double newQ_bias){ Q_bias = newQ_bias; }
void FilterKalman::setRmeasure(double newR_measure) { R_measure = newR_measure; }

double FilterKalman::getQangle() { return Q_angle; }
double FilterKalman::getQbias() { return Q_bias; }
double FilterKalman::getRmeasure() { return R_measure; }





