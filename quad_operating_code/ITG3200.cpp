#include "Sensor.h"
#include "ITG3200.h"


ITG3200::ITG3200()
:
Sensor(0xD0 >> 1)
{
  
}

void ITG3200::init(){
  writeI2C(DLPF_FS, FULLSCALE | _42HZ);
  
   zero[0] = -60;
   zero[1] = 94;
   for (int i =0; i < 3; i++) lastVal[i] = 0;
}

void ITG3200::get_zeros(){
   int sampleLimit = 10;
  for (int i = 0; i < sampleLimit; i++){
   read();
   zero[0] += (double)buffer[0];
   zero[1] += (double)buffer[1];
   zero[2] += (double)buffer[2];
   delay(100);
  }
  zero[0] /= sampleLimit;
  zero[1] /= sampleLimit;
  zero[2] /= sampleLimit;
}

void ITG3200::read(){
  byte bytes[6];
  memset(bytes,0,6);
 
  readI2C(DATA_REG, bytes, 6);
  
  for (int i = 0; i < 3; i++){
    lastVal[i] = buffer[i];
    buffer[i] = (int)bytes[2*i+1] + (((int)bytes[2*i]) << 8); 
  }
}

/**
* Outputs as degrees/second.
*/
double ITG3200::getAxis(int i){
  double axis = ((double)buffer[i] - zero[i]);
  return axis;
}

double ITG3200::getX(){
  return getAxis(0); 
}
double ITG3200::getY(){
  return getAxis(1); 
}
double ITG3200::getZ(){
  return getAxis(2); 
}


