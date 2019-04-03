
#ifndef uartHpp
#define uartHpp

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


#define ERROR_OPEN_UART -10

#define ERROR_NO_RETURN_MESSAGE -20

#define ERROR_TXUART_CLOSED -30
#define ERROR_TXUART        -31


// Arduino ERROR codes
#define ERROR_ASW            'F'
#define ERROR_MSG_LENGTH      1
#define ERROR_COMPONEND       2
#define ERROR_OPTYPE          3

#define MSG_SRT             0xFE



static const int messageLength = 1 + 1 + 1 + 4;//Start + Identifierer + OP Type + Value
static int verify = 0;

int setupUART(int, char*);
int rxUART(int, char[]);
int txUART(int, char[]);
void printv(const char*);



#endif
