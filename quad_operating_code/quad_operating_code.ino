#include "Sensor.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "HMC5883L.h"
#include <Wire.h>

ADXL345* accel = new ADXL345;
ITG3200* gyro = new ITG3200;
HMC5883L* magneto = new HMC5883L;

float yaw;
float pitch;
float roll;

unsigned timer;

void setup(){
  Wire.begin();
  accel->init();
  gyro->init();
  magneto->init();
  timer = micros();
  Serial.begin(57000);
  
  gyro->zero[0] = -50;
  gyro->zero[1] = 95;
  gyro->zero[2] = -42;
}

double gyro_X = 0;
double gyro_Y = 0;
double gyro_Z = -90;

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

  gyro_X += gyro->getX()*.0069;
  gyro_Y += gyro->getY()*.0069;
  gyro_Z += gyro->getZ()*.0069;
  
  double cX = (0.97)*gyro_X + (0.03)*accel->getX();
  double cY = (0.97)*gyro_Y + (0.03)*accel->getY();
  double cZ = (0.97)*gyro_Z + (0.03)*accel->getZ();
  
  Serial.print(cX);
  Serial.print(",");
  Serial.print(cY);
  Serial.print(",");
  Serial.print(cZ);
  Serial.println(" ");
  
//  accel->print();
//  
//  Serial.print("Gyro: ");
//  Serial.print(gyro_X);
//  Serial.print(",");
//  Serial.print(gyro_Y);
//  Serial.print(",");
//  Serial.print(gyro_Z);
//  Serial.println(" ");
//  
//  magneto->print();
  
  timer = micros();
  delay(100); // 100Hz
}
