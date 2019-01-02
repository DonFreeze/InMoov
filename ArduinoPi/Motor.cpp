#include "Servo.h"
#include "Motor.h"
//#include <Serial.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif




void Motor::init(int set_pin, int set_angle, int set_max_angle, int set_min_angle)
{
    myservo.attach(set_pin);  // attaches the servo on pin 9 to the servo object

    max_angle = set_max_angle;
    min_angle = set_min_angle; 
    pin = set_pin;
    setAngle(set_angle);
    


}

/* Sets the angle between 0 and 180 degree*/
void Motor::setAngle(int set_angle)
{

    if ((set_angle > angle) && (set_angle <= max_angle))
    {       
        for (; angle <= set_angle; angle++) { 
            myservo.write(angle);
            delay(15);
        }
    }
    else if  ((set_angle < angle) && (set_angle >= min_angle))
    {
        for (; angle >= set_angle; angle--) { 
            myservo.write(angle);
            delay(15);
        }
    }



}


int Motor::getAngle()
{
    return angle;
}