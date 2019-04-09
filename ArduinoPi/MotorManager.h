/* Robo Project
 * Servo Motor Class
 */

#include "Arduino.h"
#include <VarSpeedServo.h>

#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#define MOTOR_NUMBER 2

struct MotorValues
{
    unsigned char vertical;
    unsigned char horizontal;
    unsigned char speed;
};


class MotorManager
{

public:
    MotorManager();
    void updateMotors(unsigned char* values); 
    void turnHeadToAngle(MotorValues* head_values);
    void turnEyesToAngle(MotorValues* eyes_values);

private:

    VarSpeedServo myservo[MOTOR_NUMBER]; 
    
};
#endif
