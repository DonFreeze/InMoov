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
        Serial.println(ERROR_MsgToLong);
        return;
      }
      interpret(&command[0]);
      messageLength = 0;
      memset(&command[0], 0, MAX_MSG_LENGTH);
  }else if(recived == MSG_SRT && messageLength>0){
      Serial.println(ERROR_NoMsgEnd);
      messageLength=0;  //Fehlerhafte message ohne endezeichen wird verworfen
      memset(&command[0], 0, MAX_MSG_LENGTH);
      command[messageLength] = recived;
      messageLength++;
  }else{
      command[messageLength] = recived;
      messageLength++;
  }      
}



