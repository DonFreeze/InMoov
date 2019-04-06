

#include "MotorManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


MotorManager::MotorManager()
{
  
  for (int i = 0; i < MOTOR_NUMBER; i++)
  {
   // VarSpeedServo myservo[i];
    
    myservo[i].attach(7+i);
    myservo[i].write(90,100,true);
  }
}



void MotorManager::updateMotors(unsigned char* values)
{ 
  for (int i = 0; i < MOTOR_NUMBER; i++)
  {
    myservo[i].write(values[i],20,true);
  }

}
