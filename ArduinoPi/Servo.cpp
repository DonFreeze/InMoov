#include "Servo.h"
#include "Motor"
//#include <Serial.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif




void Motor::Motor(int pin, int angle)
{
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
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