#include "Sensor.h"
#include "HMC5883L.h"


HMC5883L::HMC5883L()
:Sensor(0x3C >> 1)
{
   
}

void HMC5883L::init(){
  writeI2C(MEASURE_MODE_REG, MEASURE_MODE_CONTINUOUS);
}

void HMC5883L::read(){
  byte bytes[6];
  memset(bytes,0,6);
  
  readI2C(DATA_REG, bytes, 6);
  
  for (int i = 0; i < 3; i++)
     buffer[i] = (((int)bytes[2*i]) << 8) + (int)bytes[2*i+1];
}

void HMC5883L::print(){
  
//  Serial.print("Magneto: ");
//  Serial.print(getX());
//  Serial.print(",");
//  Serial.print(getY());
//  Serial.print(",");
//  Serial.print(getZ());
//  Serial.println(" ");
}


