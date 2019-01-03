/* Robo Project
 * Servo Motor Class
 */
#include <Servo.h>
#include "Arduino.h"


class MotorManager
{

public:
    int SetNewPosition(int* values);

private:

    Motor motor[5]; 
};

