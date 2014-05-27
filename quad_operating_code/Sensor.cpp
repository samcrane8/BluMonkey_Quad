#include <Wire.h>

#include "Sensor.h"
#include "Arduino.h"

Sensor::Sensor(byte address){
  this->address = address;
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


