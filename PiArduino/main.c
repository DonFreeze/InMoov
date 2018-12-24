#include "uart.h"

void showHelp(char*);


int main(int argc, char* argv[]){

    extern char *optarg;
    int option;

    char *port = "/dev/ttyAMA0"; 
    int baud = B9600;
    char message[maxMessageLength];
    int messageLength = 4;

    
    for(int i=0; i<maxMessageLength; i++)
        message[i] = '\0';
    message[0] = '\1';
    message[1] = 10;
    message[2] = 2;

    while((option = getopt(argc, argv, "m:b:p:hv")) != -1){
	switch(option){
	    case 'm':
            if(strlen(optarg) >= maxMessageLength){
                printf("Message to long!\n");
                return -1;
            }
            messageLength = strlen(optarg) + 2;
            strcat(message, optarg);
            if(verify)
                printf("message: %s\n",message);
            break;
	    case 'b':
            baud = atoi(optarg);
            if(verify)
                printf("baud: %d\n",baud);
            break;
        case 'p':
            port = (char*) malloc(6 + strlen(optarg));
            strcat(port, "/dev/");
            strcat(port, optarg);
            if(verify)
                printf("port: %s\n",port);
            break;
        case 'v':
            verify = 1;
            break;
        case 'h':
            showHelp(argv[0]);
            return 0;
        case '?':
            printf("Undefined parameter: Try '%s -h' for more information\n", argv[0]);
            return -3;
        }
    }

    int uart = setupUART(baud, port);
    if(uart < 0){
        printf("An error occured! Try -h for help or run with -v for more information\n");
        return -1;
    }
    
    if(txUART(uart, message, messageLength) < 0)
        printf("An error occured! Try -h for help or run with -v for more information\n");

    close(uart);

    
    return 0;
}

void showHelp(char* progName){
    printf("Usage: %s [OPTION] . . . \n", progName);
    printf("Usage without parameter will send a Ping with standard parameters\n\n");
    printf("-h \t\tShows this help\n");
    printf("-m message\t%d Byte message send to Arduino\n",maxMessageLength-2);
    printf("-b baudrate\tBaudrate for the connection, standard is B9600\n");
    printf("-p port\t\tUSB Port Arduino is connected, standard is ttyAMA0\n");
    printf("-v \t\tMore informations are displayed during run\n");
}

