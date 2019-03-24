/* Robo Project
 * Servo Motor Class
 */

#include "Arduino.h"
#include "Motor.h"

#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H


class MotorManager
{

public:
    MotorManger();
    void init();
    void updateMotors(int* values); 
private:
    int num_motors;
    Motor motor[5];
    
};
#endif
