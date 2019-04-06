/* Robo Project
 * Arduino Interpreter for the Raspberry Pi commands
 * Commands are specified in ReadMe file
 */
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "MotorManager.h"

#define TOTAL_MSG_LENGTH 7
#define MSG_START_SEQ   0xFE

#define STATUS  0x10
#define EYE     0x20
#define MOTOR   0x30
#define WRITE   0x01
#define READ    0x02


// ERROR Codes
#define ERROR_ASW             'F'
#define ERROR_MSG_LENGTH      0x01
#define ERROR_COMPONEND       0x02
#define ERROR_OPTYPE          0x03

class Interpreter
{
public:
    Interpreter();
     void interpret(unsigned char* message);

private:
     bool messageIsValid();
     void buildErrorMessage(unsigned char);
     MotorManager* motor_manager;
};




#endif
