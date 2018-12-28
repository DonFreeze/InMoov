#include "interpreter.h"
//#include <Serial.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

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

    if(command[0] != MSG_SRT){
      Serial.println(ERROR_NoMsgStart);
      return;
    }
    componend = &command[1];
    opType = &command[2];
    typeNumber = &command[3];
    data1 = &command[4];
    data2 = &command[5];
    
    switch(componend[0]){
        case MOTOR:
            if(opType[0] == 'R')
                motorRead();
            else if(opType[0] == 'W')
                motorWrite();
            else
                Serial.println(ERROR_MsgOpType);
            break;
        case EYE:
            if(opType[0] == 'R')
                eyeRead();
            else if(opType[0] == 'W')
                eyeWrite();
            else
                Serial.println(ERROR_MsgOpType);
            break;
        case STATUS:
            Serial.println(STATUS_MSG);
            break;
        default:
            Serial.println(ERROR_NoComponendMatch);
            break;
    }
    Serial.println(command);
}






