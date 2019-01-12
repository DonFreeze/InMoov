
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

#define ERROR_COMPONEND     -41
#define ERROR_OPTYPE        -42
#define ERROR_TYPENUMBER    -43


static const int maxMessageLength = 1 + 1 + 1 + 4 + 1;//Start + Identifierer + OP Type + Value + \0
static int verify = 0;

int setupUART(int, char*);
int rxUART(int, char[]);
int txUART(int, char[], int);
void printv(const char*);



#endif
