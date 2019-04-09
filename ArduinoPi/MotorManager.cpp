

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

void turnHeadToAngle(MotorValues* head_values)
{
  if (head_values != NULL)
  {
    myservo[7].write(head_values.horizontal,head_values.speed);
    myservo[8].write(head_values.vertical,head_values.speed);
  }

}

void turnEyesToAngle(MotorValues* eyes_values)
{
  if (eyes_values != NULL)
  {
    myservo[9].write(eyes_values.horizontal,eyes_values.speed);
    myservo[10].write(eyes_values.vertical,eyes_values.speed);
  }

}