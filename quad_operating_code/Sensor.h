#ifndef SENSOR_H
#define SENSOR_H

#include "Arduino.h"

class Sensor{
  public:
     Sensor();
     ~Sensor();
     virtual void init()= 0;
     virtual bool read()= 0;
  private: 
     byte address;
};

#endif // SENSOR_H
