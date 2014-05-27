#include <Servo.h>

int power;

Servo motor [2];

int startTime = 0;

const int DELAY = 3000;

void setup(){
  motor[0].attach(3);
  motor[1].attach(11);
  Serial.begin(57600);
}

void loop(){
  if (Serial.available() > 0){
     int i = Serial.parseInt();
    
     if ( i > 0 && i < 180){
       power = i;
       Serial.print("Setting power to : ");
       Serial.println(power);
     } else { Serial.println("Not a valid number."); }
  }
     motor[0].write(power);
     motor[1].write(power);
}
