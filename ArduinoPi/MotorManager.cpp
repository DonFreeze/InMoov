
#include "MotorManager.h"
//#include <Serial.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


void MotorManager::init()
{
  motor[0].init(6, 80, 160, 40); // mid 80
  motor[1].init(7, 70, 160, 30); // mid 80
  motor[2].init(8, 80, 120, 40); // mid 80
  motor[3].init(9, 70, 160, 70); // mid 80
  motor[4].init(10, 80, 120, 40); // mid 80

}



int MotorManager::setNewPosition(int* values)
{
    Serial.println("MotorManager:setNewPosition");
    bool loop = true;
    int motor_index = 0;
    int done_count = 0;
  
    
    while (loop != false)
    {
        
        done_count = 0;
        for (int i = 0; i < 5; i++)
        {
            done_count += (motor[i].setAngle(values[i]) == true) ? 1 : 0;
           /* Serial.print(values[i]);
            Serial.print("\t");  
            Serial.print(i);
            Serial.print("\t"); */
        }
        delay(15);
        
        loop = (done_count == 5) ? false : true;
        Serial.print(done_count);
        Serial.print("\t"); 
        
    }
    return 0;
}
