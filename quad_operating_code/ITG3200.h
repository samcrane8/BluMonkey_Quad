

#ifndef ITG3200_H
#define ITG3200_H

#include "Sensor.h"

class ITG3200 : public Sensor{
  
  public:
     ITG3200();
     void init();
     void read();
     void print();
     int getX();
     int getY();
     int getZ();
  protected:
     static const char DATA_REG = 0x1D;
     static const char DLPF_FS = 0x16;
     static const char FULLSCALE = 0x03 << 3;
     static const char _42HZ = 0x03;

};

#endif //HMC5883L_H
