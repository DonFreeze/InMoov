/* Robo Project
 * Servo Motor Class
 */

#include "Arduino.h"
#include "Motor.h"

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
