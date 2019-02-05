
#if 0
#include "Motor.h"
#include <math.h>

//#include <Serial.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


void Motor::init(int set_pin, int angle_2_set, int set_max_angle, int set_min_angle)
{ 
    max_angle = set_max_angle;
    min_angle = set_min_angle; 
    pin = set_pin;
    curr_angle = angle_2_set;
    myservo.attach(pin);
    myservo.write(curr_angle);
}



/* Increments or decrements the current angle for 1 degree to match the angle_2_set. 
 * returns true, if angle_2_set is reached, else false.   
 */
void Motor::updateAngle(int angle_2_set)
{ 

  
  if (angle_2_set >= max_angle)
  {
    curr_angle = max_angle;
  }
  else if (angle_2_set <= min_angle)
  {
    curr_angle = min_angle;
  }
  else 
  {
    curr_angle = angle_2_set;
  }
  myservo.write(curr_angle);
}



int Motor::getCurrAngle()
{
    return curr_angle;
}

int Motor::getMinAngle()
{
    return min_angle;
}

int Motor::getMaxAngle()
{
    return max_angle;
}

#endif

