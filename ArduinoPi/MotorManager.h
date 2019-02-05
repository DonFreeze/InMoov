/* Robo Project
 * Servo Motor Class
 */
#if 0
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
#endif

