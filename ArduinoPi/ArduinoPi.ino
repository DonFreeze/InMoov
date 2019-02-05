#include "interpreter.h"

unsigned char message[TOTAL_MSG_LENGTH+1];
int messageLength = 0;
bool start = false;
  
void setup(){
    Serial.begin(9600);
    message[TOTAL_MSG_LENGTH] = '\n';
}
 
void loop(){
    if (Serial.available()) {
        unsigned char recived = Serial.read();
        //if(recived){
          buildMessage(recived);
        //}
    }
}

void buildMessage(unsigned char recived){
  if(recived == MSG_SRT){
    resetMessage();
    start = true;
  }
  if(!start)
    return;

  message[messageLength] = recived;
  messageLength++;    
  if(messageLength == TOTAL_MSG_LENGTH){
    interpret(&message[0]);
    resetMessage();
  }  
}

void resetMessage(){
  messageLength = 0;
  //memset(&message[0], 0, TOTAL_MSG_LENGTH-1);
  start = false;
}








