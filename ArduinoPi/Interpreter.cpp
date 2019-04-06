#include "Interpreter.h"


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

unsigned char *msg;

// TODO create a List of all Components
// Componend List has instances like motor and led
// Create an Interpreter Object and do that in the Konstruktor?

Interpreter::Interpreter(){
  
    motor_manager = new MotorManager();
  
}


void Interpreter::interpret(unsigned char* message){
    msg = message;

    if(messageIsValid()){
      motor_manager->updateMotors(msg[3]);      
    }
}

bool Interpreter::messageIsValid(){
  // Conponend bigger than List index? error
  // To big values? Is it posible to validate that?
  
  // Example Code!
  if(msg[1] > 0x30){
    buildErrorMessage(ERROR_COMPONEND);
    return false;
  }
  if(msg[2] > 0x10){
    buildErrorMessage(ERROR_OPTYPE);
    return false;
  }
  return true;
}

void Interpreter::buildErrorMessage(unsigned char errorType){
  msg[2] = ERROR_ASW;
  msg[3] = errorType;
  msg[4] = '\0';
}
