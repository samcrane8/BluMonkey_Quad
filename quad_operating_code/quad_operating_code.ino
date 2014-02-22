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

int x = 0;

void loop(){
  accel->read();
  gyro->read();
  x += .1*(gyro->getX()*0.98)+.01*(0.02*accel->getX());
  Serial.print(x);
  Serial.println(" ");
  delay(100); // 10Hz
}
