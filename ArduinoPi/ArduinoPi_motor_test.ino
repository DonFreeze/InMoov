#include "MotorManager.h"
#include "Servo.h"


const float pi = 3.14;
MotorManager manager; 
int value[2];



void setup(){
  Serial.begin(9600);
  value[0] = 80;
  value[1] = 80;
 /* value[2] = 50;
  value[3] = 50;
  value[4] = 50;*/
 
  manager.init();

}

 
void loop(){

    // seqence 1:  Searching left to right
  for (int i = 0; i <= 3; i++)
  {
    value[0] = 40; // 40 deg =  left from his perspective  90° = mid
    value[1] = 90; // 40 deg =  UP 90° = mid
    manager.updateMotors(value);
    delay(400);
    value[0] = 140; // 140 deg =  right from his perspective  90° = mid
    value[1] = 90; // 40 deg =  UP 90° = mid
    manager.updateMotors(value);
    delay(400);
  }
   value[0] = 90; // 140 deg =  right from his perspective  90° = mid
   value[1] = 90; // 40 deg =  UP 90° = mid
   manager.updateMotors(value);
   delay(1000);

// sequence 2: thinking 
  delay(800);
  value[0] = 140; // 140 deg =  right from his perspective  90° = mid
  value[1] = 40; // 40 deg =  UP 90° = mid
  manager.updateMotors(value);
  delay(4000);
  value[0] = 90; // 140 deg =  right from his perspective  90° = mid
  value[1] = 90; // 40 deg =  UP 90° = mid
  manager.updateMotors(value);
  delay(1000);

// sequence 3: random 
  random(10, 20);
  for (int i = 0; i <= 80; i++)
  {
    value[0] = random(40, 140);
    value[1] = random(40, 140);
    manager.updateMotors(value);
    delay(200);
  }
   value[0] = 90; // 140 deg =  right from his perspective  90° = mid
   value[1] = 90; // 40 deg =  UP 90° = mid
   manager.updateMotors(value);
   delay(1000);


// sequence 4: circle
/*  for (int k = 0; k <= 360; k+=5)
  {
    value[0] = (int)(50*sin(k/(2*pi))+90); 
    value[1] = (int)(50*cos(k/(2*pi))+90); 
    Serial.print((int)(50*sin(k/(2*pi))+90));
    Serial.print("\t");
    manager.updateMotors(value);
    delay(90);
  }
 value[0] = 90; // 140 deg =  right from his perspective  90° = mid
   value[1] = 90; // 40 deg =  UP 90° = mid
   manager.updateMotors(value);
   delay(1800);
  */

/*
  
  value[0] = 140; // 40 deg =  left from his perspective  90° = mid
  value[1] = 40; // 40 deg =  UP 90° = mid
  manager.updateMotors(value);
  delay(800);

  value[0] = 140; // rigt
  value[1] = 150; // 150 deg =  down
  manager.updateMotors(value);
  delay(800);*/
}
