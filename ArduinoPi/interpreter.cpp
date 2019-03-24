#include "interpreter.h"


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

unsigned char *msg;

void motorRead(){
    //is there somthing to read?
    //digitalRead(pin);
}
void motorWrite(){
    //Set motor angle
    //digitalWrite(pin, HIGH);

}

void eyeRead(){
    //is there something to read?
}
void eyeWrite(){
    //set LED Eye on/off, color
}

void interpret(unsigned char* message, MotorManager* mm_ptr){
  msg = message;
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

void buildErrorMessage(unsigned char errorType){
  msg[2] = ERROR_ASW;
  msg[3] = errorType;
}
