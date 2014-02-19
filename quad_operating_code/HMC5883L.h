#ifndef HMC5883L_H
#define HMC5883L_H

#include "Sensor.h"

class HMC5883L : public Sensor{
  public:
     HMC5883L();
     void init();
     void read();
     void print();
  protected:
     static const char DATA_REG = 0x03;
     static const char MEASURE_MODE_REG = 0x02;
     static const char MEASURE_MODE_CONTINUOUS = 0x00;
  
};

#endif //HMC5883L_H
