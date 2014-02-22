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
}

int ADXL345::getX(){ return buffer[0]; }
int ADXL345::getY(){ return buffer[1]; }
int ADXL345::getZ(){ return buffer[2]; }

void ADXL345::read(){
  byte bytes[6];
  memset(bytes,0,6);
  readI2C(DATA_REG,bytes,6);
  
  for (int i = 0; i < 3; i++)
     buffer[i] = (((int)bytes[2*i+1]) << 8) + (int)bytes[2*i];
}

void ADXL345::print(){
  int x = buffer[0]; 
  int y = buffer[1];
  int z = buffer[2];
  
  Serial.print("Accelerometer: ");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println(" ");
}


