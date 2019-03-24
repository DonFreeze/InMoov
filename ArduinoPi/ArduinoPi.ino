#include "interpreter.h"
#include "MotorManager.h"

unsigned char message[TOTAL_MSG_LENGTH+1];
int messageLength = 0;
bool start = false;

MotorManager* motor_manager = new MotorManager;
  
void setup(){
    Serial.begin(9600);
    message[TOTAL_MSG_LENGTH] = '\n';
    motor_manager->init();
    
}
 
void loop(){
    if (Serial.available()) {
        unsigned char received = Serial.read();
        if(received){
          buildMessage(received);
        }
    }
}

void buildMessage(unsigned char received){
  if(charNotStart(received))
    return;

  message[messageLength] = received;
  messageLength++;    
  if(messageLength == TOTAL_MSG_LENGTH){
    interpret(&message[0], motor_manager);
    resetMessage();
  }  
}

int charNotStart(unsigned char received){
  if(received == MSG_SRT){
    resetMessage();
    start = true;
  }
  if(!start)
    return -1;

  return 0;
}

void resetMessage(){
  messageLength = 0;
  start = false;
}
