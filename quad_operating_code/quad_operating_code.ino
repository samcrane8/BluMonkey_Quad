#include "Sensor.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "HMC5883L.h"
#include <Wire.h>

ADXL345* accel = new ADXL345;
ITG3200* gyro = new ITG3200;
HMC5883L* magneto = new HMC5883L;

void setup(){
  Wire.begin();
  accel->init();
  gyro->init();
  magneto->init();
  
  Serial.begin(57000);
}

void loop(){
  accel->read();
  accel->print();
  gyro->read();
  gyro->print();
  magneto->read();
  magneto->print();
  delay(500); // 2Hz
}
