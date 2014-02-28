#ifndef PID_H
#define PID_H

class PID {
  public:
    PID(float K_p, float K_i, float K_d);
    float get(float desired, float actual);
  private:
    float getP(float error);
    float getD(float error);
    float K_p;
    float K_i;
    float K_d;
    float lastError;
};

#endif 
