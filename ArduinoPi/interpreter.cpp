#include "interpreter.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

char *start;
char *componend;
char *opType;
char *typeNumber;
char *data1;
char *data2;

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

void interpret(char *command){

    start = &command[0];
    componend = &command[1];
    opType = &command[2];
    typeNumber = &command[3];
    data1 = &command[4];
    data2 = &command[5];
    
    switch(componend[0]){
        case MOTOR:
            if(opType[0] == READ)
                motorRead();
            else if(opType[0] == WRITE)
                motorWrite();
            else
                Serial.println(buildErrorString(componend, ERROR_OPTYPE));
            break;
        case EYE:
            if(opType[0] == READ)
                eyeRead();
            else if(opType[0] == WRITE)
                eyeWrite();
            else
                Serial.println(buildErrorString(componend, ERROR_OPTYPE));
            break;
        case STATUS:
            Serial.println(buildAnswerString());
            break;
        default:
            Serial.println(buildErrorString(componend, ERROR_COMPONEND));
            break;
    }
    Serial.println(command);
}

char* buildAnswerString(){
    typeNumber = MSG_END;
    data1 = '\n';
    return start;
}






