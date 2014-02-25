#include "Sensor.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "HMC5883L.h"
#include "FilterKalman.h"
#include <Wire.h>

ADXL345* accel = new ADXL345;
ITG3200* gyro = new ITG3200;
HMC5883L* magneto = new HMC5883L;

float yaw;
float pitch;
float roll;

FilterKalman kalmanPitch;
FilterKalman kalmanRoll;

unsigned timer;

void setup(){
  Wire.begin();
  accel->init();
  gyro->init();
  magneto->init();
  timer = micros();
  Serial.begin(57000);
  kalmanPitch.setAngle(180);
  kalmanRoll.setAngle(180);
}

double gyro_roll = 0;
double gyro_pitch = 0;
double gyro_yaw = 0;

void loop(){
  accel->read();
  
//  Serial.print("Accel: ");
//  Serial.print(accel->getX());
//  Serial.print(",");
//  Serial.print(accel->getY());
//  Serial.print(",");
//  Serial.print(accel->getZ());
//  Serial.println(" ");
  gyro->read();
  double deltaTime = (micros()-timer)/1000000;
  
  double roll_vel = (gyro->getX() + gyro->lastVal[0])/2;
  roll_vel *= 0.00086;
  gyro_roll += roll_vel;
  double pitch_vel = (gyro->getY()+gyro->lastVal[1])/2;
  pitch_vel *= 0.00086;
  gyro_pitch += pitch_vel;
  
//  Serial.print(accel->buffer[0]);
//  Serial.print(",");
//  Serial.print(accel->buffer[1]);
//  Serial.print(",");
//  Serial.print(accel->buffer[2]);
//  Serial.println(" ");
  
  double acc_pitch = atan(accel->buffer[0]/sqrt(pow(accel->buffer[1],2) + pow(accel->buffer[2],2)))*RAD_TO_DEG;

  double acc_roll = atan(accel->buffer[1]/sqrt(pow(accel->buffer[0],2) + pow(accel->buffer[2],2)))*RAD_TO_DEG;

  
  double c_roll= (0.97)*gyro_roll + (0.03)*acc_roll;
  double c_pitch = (0.97)*gyro_pitch + (0.03)*acc_pitch;
  
  double k_roll = kalmanRoll.getAngle(acc_roll,gyro_roll,
                                   (double)(micros() - timer));
  double k_pitch = kalmanPitch.getAngle(acc_pitch,gyro_pitch,
                                    (double)(micros()-timer));
  
//  accel->print();
//  
//  Serial.print("Gyro: ");
  Serial.print(k_roll);
  Serial.print(",");
  Serial.print(k_pitch);
  Serial.println(" ");
//  
//  magneto->print();
  
  timer = micros();
  delay(10); // 100Hz
}
