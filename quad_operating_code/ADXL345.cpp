#include "Sensor.h"
#include "Arduino.h"
#include "ADXL345.h"

ADXL345::ADXL345()
:Sensor(0x53)
{
  
}

void ADXL345::init(){
  //set range +/- 4G
  writeI2C(DATA_FORMAT, 0x01);
  //put into measurement mode.
  writeI2C(POWER_CTL, 0x08);
  
  zero[0] = -28;
  zero[1] = 6;
  zero[2] = -20;
}

void ADXL345::read(){
  byte bytes[6];
  memset(bytes,0,6);
  readI2C(DATA_REG,bytes,6);
  
  for (int i = 0; i < 3; i++)
     buffer[i] = (((int)bytes[2*i+1]) << 8) + (int)bytes[2*i];
}

double ADXL345::getX(){
  double y = (double)buffer[1] - zero[1];
  double z = (double)buffer[2] - zero[2];
  double angle = (atan2(-y,-z)+PI)*RAD_TO_DEG;
  return angle;
}

double ADXL345::getY(){
  double x = (double)buffer[0] - zero[0];
  double z = (double)buffer[2] - zero[2];
  double angle = (atan2(-x,-z)+PI)*RAD_TO_DEG;
  return angle;
}

double ADXL345::getZ(){
  double y = (double)buffer[1] - zero[1];
  double x = (double)buffer[0] - zero[0];
  return (atan2(-y,-x)+PI)*RAD_TO_DEG; 
}

void ADXL345::print(){
  Serial.print("Accelerometer: ");
  Serial.print(getX());
  Serial.print(",");
  Serial.print(getY());
  Serial.print(",");
  Serial.print(getZ());
  Serial.println(" ");
}


