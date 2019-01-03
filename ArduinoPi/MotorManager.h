/* Robo Project
 * Servo Motor Class
 */
#include "Motor.h"
#include "Arduino.h"


class MotorManager
{

public:
    int setNewPosition(int* values);
    void init();
private:

    Motor motor[5]; 
};
