#include "Interpreter.h"

unsigned char message[TOTAL_MSG_LENGTH+1];
int messageLength = 0;
Interpreter* interpreter;
  
void setup(){
  Serial.begin(9600);
  message[TOTAL_MSG_LENGTH] = '\n';
  interpreter = new Interpreter();
}
 
void loop(){
  if (Serial.available() > 0){
    readOnSerial();
  }
}

void readOnSerial(){
  unsigned char receivedByte = Serial.read();
  if(receivedByte == 0xFF)
    return;
  
  buildMessage(receivedByte);
  interpretCompleteMessage();
}

void buildMessage(unsigned char receivedByte){
  if(checkMessageStart(receivedByte)){
    addToMessage(receivedByte);
  }
}

bool checkMessageStart(unsigned char receivedByte){
  if(receivedByte == MSG_START_SEQ){
    resetMessage();
    return true;
  }
  if(messageLength > 0){
    return true;
  }
  return false;
}

void resetMessage(){
  messageLength = 0;
}

void addToMessage(unsigned char byte){
  message[messageLength] = byte;
  messageLength++;   
}

void interpretCompleteMessage(){
  if(messageLength == TOTAL_MSG_LENGTH){
    interpreter->interpret(&message[0]);
    sendAnswer();
    resetMessage();
  }  
}

void sendAnswer(){
  Serial.print((char*)message);
}
