

import processing.serial.*;
import java.io.IOException;

import cc.arduino.*;
import java.util.Scanner;

Serial myPort;
long lastTime;

float x_rot = 0;
float y_rot = 0;
float z_rot = 0;

int width = 425;
int height = 425;

void setup(){
  size(width,height,P3D);
  myPort = new Serial(this, Arduino.list()[0],57000);
  lastTime = millis();
  background(0);
}

void draw(){
  if (millis() - lastTime > 5){
    background(0);
    lastTime = millis(); 
    getData();
    pushMatrix();
    translate(width/2,height/2,0);
    rotateY(y_rot);
    rotateX(x_rot);
    fill(150,0,0);
    box(100);
    popMatrix();
  }
  
}

void getData(){
    myPort.bufferUntil('\n');
    String s = myPort.readStringUntil('\n');
    if (s == null) return;
    Scanner sc;
    if (s.contains("Accelerometer: ")){
      s = s.replace("Accelerometer: ","");    
      sc = new Scanner(s);
      sc.useDelimiter(",");
      int x = Integer.parseInt(sc.next());
      int y = Integer.parseInt(sc.next());
      x_rot = 20.0f*x;
      y_rot = 20.0f*y;
      System.out.println(x+","+y);
    }  //else if (s.contains("Gyro: ")){
//      s = s.replace("Gyro: ","");    
//      sc = new Scanner(s);
//      sc.useDelimiter(",");
//      int x = Integer.parseInt(sc.next());
//      int y = Integer.parseInt(sc.next());
//      int z = Integer.parseInt(sc.next());
//    } else if (s.contains("Magneto: ")){
//      s = s.replace("Magneto: ","");    
//      sc = new Scanner(s);
//      sc.useDelimiter(",");
//      int x = Integer.parseInt(sc.next());
//      int y = Integer.parseInt(sc.next());
//      int z = Integer.parseInt(sc.next());
//    }
}
