#ifndef FILTERKALMAN_H
#define FILTERKALMAN_H

class FilterKalman {
public:
  FilterKalman();
  double getAngle(double newAngle, double newRate, double dt);
  void setAngle(double newAngle);
  double getRate();
  void setQangle(double newQ_angle);
  void setQbias(double newQ_bias);
  void setRmeasure(double newR_measure);
  
  double getQangle(); 
  double getQbias();
  double getRmeasure();
private:
  double Q_angle; // Process noise variance for the accelerometer
  double Q_bias; // Process noise variance for the gyro bias
  double R_measure; // Measurement noise variance 
  
  double angle; // The angle calculated by the Kalman filter
  double bias; //The gyro bias
  double rate; // unbiased rate calculated from the rate
  
  double P[2][2]; // Error covariance matrix - This is a 2x2 matrix
  double K[2]; // Kalman gain - this is a 2x1 vector
  double y; // Angle difference
  double S; //estimate error
};

#endif // FILTERKALMAN_H
