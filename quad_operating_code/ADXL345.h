#ifndef ADXL345_H
#define ADXL345_H

#include "Arduino.h"
#include "Sensor.h"

class ADXL345 : public Sensor{
  public:
     ADXL345();
     void init();
     void read();
     void print();
     double getX();
     double getY();
     double getZ();  
     double zero[3];
  private:
     static const char DATA_FORMAT = 0x31;
     static const char POWER_CTL = 0x2D;
     static const char DATA_REG = 0x32; // starting point of the data.
     void get_zeros();
};

#endif // ADXL345_H

