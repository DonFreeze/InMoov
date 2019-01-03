#include "Servo.h"
#include "Motor.h"
//#include <Serial.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


void Motor::init(int set_pin, int angle_2_set, int set_max_angle, int set_min_angle)
{
    myservo.attach(set_pin); 
    max_angle = set_max_angle;
    min_angle = set_min_angle; 
    pin = set_pin;
    myservo.write(angle_2_set);
    curr_angle = angle_2_set;
}




/* Increments or decrements the current angle for 1 degree to match the angle_2_set. 
 * returns true, if angle_2_set is reached, else false.   
 */
bool Motor::setAngle(int angle_2_set)
{
    bool ret = false;
    // Serial.println("Motor:setAngle");
     
    if ((angle_2_set > curr_angle ) && (angle_2_set < max_angle ))
    {       
        curr_angle++;
      //  Serial.print(curr_angle);
      //  Serial.println("Motor curr_angle++");
        
        myservo.write(curr_angle);
    }
    else if  ((angle_2_set < curr_angle ) && (angle_2_set > min_angle ))
    {
        curr_angle--;
       // Serial.print(curr_angle);
       // Serial.println("Motor curr_angle--");
        
        myservo.write(curr_angle);
    } 
    else
    {
      ret = true;
    }
  
    if (curr_angle == angle_2_set)
    {
        ret = true;
    }
    //Serial.print(ret);
    return ret;
    
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
