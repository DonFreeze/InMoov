/* Robo Project
 * Servo Motor Class
 */

#include "Arduino.h"
#include <VarSpeedServo.h>

#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#define MOTOR_NUMBER 2

class MotorManager
{

public:
    MotorManager();
    void updateMotors(unsigned char* values); 
private:

    VarSpeedServo myservo[MOTOR_NUMBER]; 
    
};
#endif
