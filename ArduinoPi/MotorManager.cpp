
#include "MotorManager.h"
//#include <Serial.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


void MotorManager::init()
{
  motor[0].init(6, 90, 180, 0); // mid 80
  motor[1].init(7, 90, 180, 0); // mid 80
  /*motor[2].init(8, 80, 120, 40); // mid 80
  motor[3].init(9, 70, 160, 70); // mid 80
  motor[4].init(10, 80, 120, 40); // mid 80*/
}



void MotorManager::updateMotors(int* values)
{ 
  for (int i = 0; i <= NUM_MOTORS; i++)
  {
    
    motor[i].updateAngle(values[i]);
  }
  
}
