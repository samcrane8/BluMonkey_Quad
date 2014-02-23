#include <Wire.h>

#include "Sensor.h"
#include "Arduino.h"

Sensor::Sensor(byte address){
  this->address = address;
}

double Sensor::getX(){ return getAngle(0); }
double Sensor::getY(){ return getAngle(1); }
double Sensor::getZ(){ return getAngle(2); }

double Sensor::getAngle(int i){
  int axis = buffer[i];
  return axis;  
}

void Sensor::readI2C(byte reg, byte data[], byte length){
  
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.beginTransmission(address);
  Wire.requestFrom(address, length);
  
  int i = 0; 
  while(Wire.available()){
    data[i]  = Wire.read();
    i++;
  }
  Wire.endTransmission();
}

void Sensor::writeI2C(byte reg, byte val){
  Wire.beginTransmission(address); // start transmission to device 
  Wire.write(reg);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission(); 
}

