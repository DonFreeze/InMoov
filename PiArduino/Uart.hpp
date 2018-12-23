
#ifndef uartHpp
#define uartHpp

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


static const int maxMessageLength = 1 + 1 + 1 + 4 + 1;//Start + Identifierer + OP Type + Value + \0
static int verify = 0;

int setupUART(int, char*);
int rxUART(int, char[]);
int txUART(int, char[], int);
void printv(const char*);



#endif
