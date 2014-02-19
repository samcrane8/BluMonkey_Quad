#include "Sensor.h"
#include "ITG3200.h"


ITG3200::ITG3200()
:
Sensor(0xD0 >> 1)
{

}

void ITG3200::init(){
  writeI2C(DLPF_FS, FULLSCALE | _42HZ);
}

void ITG3200::read(){
  byte bytes[6];
  memset(bytes,0,6);

  readI2C(DATA_REG, bytes, 6);

  for (int i = 0; i < 3; i++){
    buffer[i] = (int)bytes[2*i+1] + (((int)bytes[2*i]) << 8); 
  }
}

void ITG3200::print(){
  int x = buffer[0]; 
  int y = buffer[1];
  int z = buffer[2];

  Serial.print("Gyro: ");
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.print(" , ");
  Serial.print(z);
  Serial.println();
}

