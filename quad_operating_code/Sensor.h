#include <Wire.h>

#ifndef SENSOR_H
#define SENSOR_H

#include "Arduino.h"

class Sensor{
  public:
     Sensor(byte address);
     virtual void init()= 0;
     virtual void read()= 0;
     virtual void print() = 0;
     int buffer[3];
  protected:
     void readI2C(byte reg, byte data[], byte length);
     void writeI2C(byte reg, byte val);
     byte address;
};

#endif // SENSOR_H
