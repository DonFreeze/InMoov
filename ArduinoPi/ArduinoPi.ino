#include "interpreter.h"

unsigned char command[MAX_MSG_LENGTH];
int messageLength = 0;
  
void setup(){
    Serial.begin(9600);
}
 
void loop(){
    if (Serial.available()) {
        unsigned char recived = Serial.read();
        if(recived){
          checkRecivedChar(recived);
        }else{
          messageLength=0;
        }
    }
}

void checkRecivedChar(char recived){
  if(recived == MSG_END){
      if(messageLength > MAX_MSG_LENGTH){
        Serial.println(buildErrorString(command[1], ERROR_MSG_LENGTH));
        return;
      }
      interpret(&command[0]);
      messageLength = 0;
      memset(&command[0], 0, MAX_MSG_LENGTH);
  }else{
      command[messageLength] = recived;
      messageLength++;
  }      
}

char* buildErrorString(char id, char errorType){
    char msg[6];
    msg[0] = 0x255;
    msg[1] = id;
    msg[2] = ERROR_ASW;
    msg[3] = errorType;
    msg[4] = 0x255;
    msg[5] = '\n';

    return (char*)  &msg[0];
}



