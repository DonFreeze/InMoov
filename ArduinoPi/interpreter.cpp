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

void Interpreter::interpret(unsigned char* message, MotorManager* mm_ptr){
    msg = message;

    if(messageIsValid()){

    }
}

bool Interpreter::messageIsValid(){
  // Conponend bigger than List index? error
  // To big values? Is it posible to validate that?
  return false;
}

void Interpreter::buildErrorMessage(unsigned char errorType){
  msg[2] = ERROR_ASW;
  msg[3] = errorType;
  msg[4] = '\0';
}
