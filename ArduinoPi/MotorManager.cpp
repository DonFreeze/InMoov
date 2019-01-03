#include "Servo.h"
#include "MotorManager.h"
//#include <Serial.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


void MotorManager::init()
{
 

}



int MotorManager::SetNewPosition(int* values)
{
    bool loop = true;
    int motor_index = 0;
    int max_diff = 0;

    while (loop != false)
    {
        
        for (int i = 0; i <= sizeof(values), i++)
        {
            motor[i].setAngle(values);
        }
        // TODO exit the loop
  

        


        delay(15);
    }
}