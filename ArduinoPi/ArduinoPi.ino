#include "interpreter.h"
#include "MotorManager.h"

unsigned char message[TOTAL_MSG_LENGTH+1];
int messageLength = 0;
bool start = false;
  
void setup(){
    MotorManger manager;
    Serial.begin(9600);
    message[TOTAL_MSG_LENGTH] = '\n';
}
 
void loop(){
    if (Serial.available()) {
        unsigned char received = Serial.read();
        //if(received){
          buildMessage(received);
        //}
    }
}

void buildMessage(unsigned char received){
  if(received == MSG_SRT){
    resetMessage();
    start = true;
  }
  if(!start)
    return;

  message[messageLength] = received;
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








