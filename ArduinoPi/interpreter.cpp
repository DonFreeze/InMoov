#include "Interpreter.h"


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

unsigned char *msg;


void Interpreter::interpret(unsigned char* message, MotorManager* mm_ptr){
  msg = message;
  digitalWrite(2, HIGH);
    switch(msg[1]){
        case MOTOR:
            
            if(msg[2] == READ)
            {
                mm_ptr->updateMotors(msg[3]);        
            }
            else if(msg[2] == WRITE)
                motorWrite();
            else
                buildErrorMessage(ERROR_OPTYPE);
            break;
            
        case EYE:
            if(msg[2] == READ)
                eyeRead();
            else if(msg[2] == WRITE)
                eyeWrite();
            else
                buildErrorMessage(ERROR_OPTYPE);
            break;
            
        case STATUS:
            // Nothing to do, just return message
            break;
            
        default:
            buildErrorMessage(ERROR_COMPONEND);
            break;
    }

    // Send Answer
    Serial.println((char*)msg);
}

void Interpreter::buildErrorMessage(unsigned char errorType){
  msg[2] = ERROR_ASW;
  msg[3] = errorType;
}
