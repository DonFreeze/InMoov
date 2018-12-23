#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

const int maxMessageLength = 1 + 1 + 4 + 1;//Identifierer + OP Type + Value, \0
int verify = 0;

void showHelp(char* progName){
    printf("Usage: %s [OPTION] . . . \n", progName);
    printf("Usage without parameter will send a Ping with standard parameters\n\n");
    printf("-h \t\tShows this help\n");
    printf("-m message\t%d Byte message send to Arduino\n",maxMessageLength);
    printf("-b baudrate\tBaudrate for the connection, standard is B9600\n");
    printf("-p port\t\tUSB Port Arduino is connected, standard is ttyAMA0\n");
    printf("-v \t\tMore informations are displayed during run\n");
}

void printv(const char *text){
    if(verify)
        printf("%s", text);
}

int rxUART(int uart0_filestream, char message[maxMessageLength]){
//----- CHECK FOR ANY RX BYTES -----
	//if (uart0_filestream != -1)
	//{
    for(int i=0; i<10; i++){    //wait 1 sec for response
		// Read up to 255 characters from the port if they are there
		char rx_buffer[256];//TODO unsigned char?
		int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
		if (rx_length < 0){
			//An error occured (will occur if there are no bytes)
		}
		else if (rx_length == 0){
			//No data waiting
		}else{
			//Bytes received
			rx_buffer[rx_length] = '\0';
            if(strstr(message, rx_buffer)){
                return 0;
            }else{
                if(verify)
			        printf("%i bytes read : %s\n", rx_length, rx_buffer);
                return -21;
            }
		}
        usleep(50000);
	}
    printv("No return value for message!\n");
    return -20;
}

int txUART(int uart0_filestream, char message[maxMessageLength]){
	
	if (uart0_filestream != -1){
		int count = write(uart0_filestream, &message[0], maxMessageLength);		//Filestream, bytes to write, number of bytes to write
		if (count < 0){
		    printv("UART TX error\n");
            return -11;
		}
        return rxUART(uart0_filestream, message);
	}
    return -10;
}

int setupUART(int baud, char *port){
	int uart0_filestream = -1;

	uart0_filestream = open(port, O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
	if (uart0_filestream == -1){
	    printv("Error - Unable to open UART.  Ensure it is not in use by another application\n");
        return -1;
	}
	
	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = baud | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);

    return uart0_filestream;
}

int main(int argc, char* argv[]){

    extern char *optarg;
    int option;

    char *port = "/dev/ttyAMA0"; 
    int baud = B9600;
    char message[maxMessageLength];
    
    for(int i=0; i<maxMessageLength; i++)
        message[i] = '\0';

    while((option = getopt(argc, argv, "m:b:p:hv")) != -1){
		switch(option){
			case 'm':
                if(strlen(optarg) >= maxMessageLength){
                    printf("Message to long!\n");
                    return -1;
                }
                strcpy(message, optarg);
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
    
    if(txUART(uart, message) < 0)
        printf("An error occured! Try -h for help or run with -v for more information\n");

    close(uart);

    
    return 0;
}