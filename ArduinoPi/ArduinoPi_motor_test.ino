#include "MotorManager.h"


MotorManager manager; 
int value[5];

void setup(){
  Serial.begin(9600);
  Serial.println("Hello world");
  value[0] = 80;
  value[1] = 80;
  value[2] = 50;
  value[3] = 50;
  value[4] = 50;
  manager.init();
}

 
void loop(){

  
  manager.setNewPosition(value);
  Serial.println("----------------->>>>Main loop");
    
  delay(100);

  value[0] = 60;
  value[1] = 150;
  manager.setNewPosition(value);
  delay(300);
  value[0] = 60;
  value[1] = 40;
  manager.setNewPosition(value);
  delay(300);
  
  value[0] = 140;
  value[1] = 40;
  manager.setNewPosition(value);
  delay(300);

  value[0] = 140;
  value[1] = 150;
  manager.setNewPosition(value);
  delay(300);
   value[0] = 60;
  value[1] = 150;
  manager.setNewPosition(value);
  delay(300);
}
