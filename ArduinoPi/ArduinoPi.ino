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
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
}
 
void loop(){
    if (Serial.available() > 0){
        unsigned char receivedByte = Serial.read();
        if(receivedByte){
          buildMessage(receivedByte);
        }
    }
}

void buildMessage(unsigned char receivedByte){
  
  if(charNotStart(receivedByte))
    return;

  message[messageLength] = receivedByte;
  messageLength++;    
  if(messageLength == TOTAL_MSG_LENGTH){
    interpret(&message[0], motor_manager);
    resetMessage();
  }  
}

int charNotStart(unsigned char receivedByte){
  if(receivedByte == MSG_START_SEQ){
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
