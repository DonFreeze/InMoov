#include "uart.h"


void printv(const char *text){
    if(verify)
        printf("%s", text);
}

int checkRecivedMessage(char *recivedMessage, char *sendMessage){
	if(strstr(recivedMessage, sendMessage))
		return 0;
	else{
		printv("Messages not equal!\n");
		return -1;
	}
}

int rxUART(int uart0_filestream, char message[maxMessageLength]){
//----- CHECK FOR ANY RX BYTES -----
	//if (uart0_filestream != -1)
	//{
    for(int i=0; i<5; i++){    //wait 0.5 sec for response
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
			//if(verify)
				printf("%i bytes read : %s\n", rx_length, rx_buffer);
			return checkRecivedMessage(rx_buffer, message);
		}
        usleep(50000);
	}
    printf("No return from message!\n");
    return -20;
}

int txUART(int uart0_filestream, char message[maxMessageLength], int messageLength){
	
	if (uart0_filestream != -1){
		int count = write(uart0_filestream, &message[0], messageLength);		//Filestream, bytes to write, number of bytes to write
		if (count < 0){
		    printf("UART TX error\n");
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
	    printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
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
