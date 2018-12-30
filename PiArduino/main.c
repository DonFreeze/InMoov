#include "uart.h"

void showHelp(char*);
void initStandardMessage(char*);
int GetArgumentAsInt(char*);
void changeBaudTo(int*, char*);

int main(int argc, char* argv[]){

    extern char *optarg;
    int option;

    char *port = "/dev/ttyAMA0"; 
    int baud = B9600;
    int data = 0;
    char message[maxMessageLength];
    int messageLength = 3;


    initStandardMessage(&message[0]);

    while((option = getopt(argc, argv, "m:d:b:p:hv")) != -1){
	switch(option){
	    case 'm':
            messageLength = strlen(optarg) + 2;
            if(messageLength >= maxMessageLength){
                printf("Message to long!\n");
                return -2;
            }
            //create message array, better way?
            char *temp = (char*) malloc(messageLength);
            strncpy(temp, "S", 1);
            strncat(temp, optarg, strlen(optarg));
            strncat(temp, "\n", 1);
            strncpy(message, temp, messageLength);

            if(verify)
                printf("message: %s\n",message);
            break;
        case 'd':
            data = GetArgumentAsInt(optarg);
            if(data>255 || data<0){
                printv("Incompatible data value!\n");
                return -2;
            }
            break;
	    case 'b':
            changeBaudTo(&baud, optarg);
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
    if(data)
        message[4] = data;
    printf("message: %s\n",message);


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

void initStandardMessage(char *message){
    message[0] = 'S';
    message[1] = 'P';
    message[2] = '\n';
}

int GetArgumentAsInt(char* value){
	if(strstr(value,"0x")){
		value[4] = '\n';	
		return (int)strtol(value,NULL,0);
	}else
		return atoi(value);
}

void changeBaudTo(int *baud, char *optarg){
    *baud = atoi(optarg);
    if(verify)
        printf("baud: %d\n",*baud);
}

void showHelp(char* progName){
    printf("Usage: %s [OPTION] . . . \n", progName);
    printf("Usage without parameter will send a Ping with standard parameters\n\n");
    printf("-h \t\tShows this help\n");
    printf("-m message\t%d Byte message send to Arduino\n",maxMessageLength-2);
    printf("-d data\tdecimal data send in message, or 0x.. as hex\n")
    printf("-b baudrate\tBaudrate for the connection, standard is B9600\n");
    printf("-p port\t\tUSB Port Arduino is connected, standard is ttyAMA0\n");
    printf("-v \t\tMore informations are displayed during run\n");
}

