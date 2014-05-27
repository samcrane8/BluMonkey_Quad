#include "Sensor.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "HMC5883L.h"
#include "FilterKalman.h"
#include <Wire.h>
#include <Servo.h>

ADXL345* accel = new ADXL345;
ITG3200* gyro = new ITG3200;
HMC5883L* magneto = new HMC5883L;

float yaw;
float pitch;
float roll;

FilterKalman kalmanPitch;
FilterKalman kalmanRoll;

Servo motor [2];

boolean settingup = false;

unsigned timer;

void setup(){
  Wire.begin();
  accel->init();
  gyro->init();
  magneto->init();
  timer = micros();
  Serial.begin(57600);
  kalmanPitch.setAngle(180);
  kalmanRoll.setAngle(180);
  motor[0].attach(3);
  motor[1].attach(11);
  arm();
}

double gyro_roll = 0;
double gyro_pitch = 0;
double gyro_yaw = 0;

double k_roll = 0;
double k_pitch = 0;

int lastTime = 0;

void loop(){
  accel->read();
  
  while (Serial.available() > 0){
     int i = Serial.parseInt();
     
     if (i == 1337){
       if (settingup)settingup = false;
       
       arm();
     }
  }
  if (settingup) {
    arm();
   return; 
  }
  
//  Serial.print("Accel: ");
//  Serial.print(accel->getX());
//  Serial.print(",");
//  Serial.print(accel->getY());
//  Serial.print(",");
//  Serial.print(accel->getZ());
//  Serial.println(" ");
  if (millis() > lastTime + 100){
  gyro->read();
  double deltaTime = (micros()-timer)/1000000;
  
  double roll_vel = (gyro->getX() + gyro->lastVal[0])/2;
  roll_vel *= 0.00086;
  gyro_roll += roll_vel;
  double pitch_vel = (gyro->getY()+gyro->lastVal[1])/2;
  pitch_vel *= 0.00086;
  gyro_pitch += pitch_vel;
  
  double acc_pitch = atan(accel->buffer[0]/sqrt(pow(accel->buffer[1],2) + pow(accel->buffer[2],2)))*RAD_TO_DEG;

  double acc_roll = atan(accel->buffer[1]/sqrt(pow(accel->buffer[0],2) + pow(accel->buffer[2],2)))*RAD_TO_DEG;

  
  double c_roll= (0.97)*gyro_roll + (0.03)*acc_roll;
  double c_pitch = (0.97)*gyro_pitch + (0.03)*acc_pitch;
  
  k_roll = kalmanRoll.getAngle(acc_roll,gyro_roll,
                                   (double)(micros() - timer));
  k_pitch = kalmanPitch.getAngle(acc_pitch,gyro_pitch,
                                    (double)(micros()-timer));
  
  if ( abs(gyro_roll - k_roll) > 5) gyro_roll = k_roll;
  if ( abs(gyro_pitch - k_pitch) > 5) gyro_pitch = k_pitch;

  Serial.print(k_roll);
  Serial.print(",");
  Serial.print(k_pitch);
  Serial.println(" ");
  
  lastTime = millis();
  timer = micros();
  }
  
  double pow = k_pitch-7;
  double m1_pow = 0.75*pow+39;
  if (m1_pow < 39) m1_pow = 39;
  if (m1_pow > 50) m1_pow = 50;
  double m2_pow = 0.5*-pow-49;
  if (m2_pow < 50) m2_pow = 49;
  if (m2_pow > 60) m2_pow = 60;
  motor[0].write(m1_pow);
  motor[1].write(m2_pow);
  
  delay(1); // 10Hz
}

void arm(){
  motor[0].write(16);
  motor[1].write(16);
  delay(3000);
}

