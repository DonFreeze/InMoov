#include "uart.h"

void showHelp(char*);
void initStandardMessage(char*);
int validateMessage(char*);

int main(int argc, char* argv[]){
    extern char *optarg;
    int option;

    // Standard configuration for communication
    char *port = "/dev/ttyAMA0"; 
    int baud = B9600;
    unsigned char message[messageLength];

    initStandardMessage(&message[0]);

    while((option = getopt(argc, argv, "m:s:b:p:hv")) != -1){
	switch(option){   
        case 'm':
            if(validateMessage(optarg) < 0)
                return -1;

            unsigned long value = strtoul(optarg, NULL, 16); 
            for(int i=messageLength-1; i>0; i--)
            {
                message[i] = value & 0xFF;
                value >>= 8;            
            }
            break;

        case 'b':
            baud = atoi(optarg);
            if(verify)
                printf("baud: %d\n",baud);
            break;

        case 'p':
            port = (char*) malloc(6 + strlen(optarg));
            strncat(port, "/dev/", 6);
            strncat(port, optarg, strlen(optarg));

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

    if(verify){
        for(int i=0; i<messageLength;i++)
            printf("message[%d]: %d\n",i,message[i]);
    }

    int uart = setupUART(baud, port);
    if(uart < 0){
        printf("An error occured! Try -h for help or run with -v for more information\n");
        return uart;
    }
    
    int messageReturn = txUART(uart, message);
    if(messageReturn < 0)
        printf("An error occured! Try -h for help or run with -v for more information\n");

    close(uart);

    
    return messageReturn;
}

void initStandardMessage(char *msg){
    memset(msg, 0, messageLength);
    msg[0] = MSG_SRT;
    msg[1] = 0x10;
}

int validateMessage(char *msg){
    while(strlen(msg) < (messageLength-1)*2){   //two input hex is one char
        strncat(msg, "0", 1);
    }
    if(strlen(msg) > (messageLength-1)*2){
        printf("Message to Long\n");
        return -1;
    }
    return 1;
}

void showHelp(char* progName){
    printf("Usage: %s [OPTION] . . . \n", progName);
    printf("Usage without parameter will send a Ping with standard parameters\n\n");
    printf("-h \t\tShows this help\n");
    printf("-m message\tmessage send to Arduino as hex, max Length is %d byte\n", messageLength-1);
    printf("-b baudrate\tBaudrate for the connection, standard is B9600\n");
    printf("-p port\t\tUSB Port Arduino is connected, standard is ttyAMA0\n");
    printf("-v \t\tMore informations are displayed during run\n");
}

void printv(const char *text){
    if(verify)
        printf("%s", text);
}

