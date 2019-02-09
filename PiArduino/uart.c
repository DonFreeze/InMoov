#include "uart.h"


int checkRecivedMessage(unsigned char *recivedMessage, unsigned char *sendMessage){
	
			for(int i=0; i<7; i++)
			printf("recived: %d\n",recivedMessage[i]);
	
	if(recivedMessage[0] != sendMessage[0] ||
		recivedMessage[1] != sendMessage[1]){

		printv("Recived != Send\n");

		return -1;
	}
	else if(recivedMessage[2] == ERROR_ASW){
		switch(recivedMessage[3]){
			case ERROR_MSG_LENGTH:
				printf("Send message to long!\n"); 
				return ERROR_MSG_LENGTH * (-1);

			case ERROR_COMPONEND:
				printf("Error Componend!\n"); 
				return ERROR_COMPONEND * (-1);

			case ERROR_OPTYPE:
				printf("Error OP Type!\n"); 
				return ERROR_OPTYPE * (-1);

			default:
				printf("Undefined Error returned!\n");
				return -1;
		}
	}else{
		//no error in message, return Data when read message
		//TODO
		printf("Success!\n");
		if(recivedMessage[3] == 0x01){
			printf("Data read: %d, %d\n", (int)recivedMessage[4], (int)recivedMessage[5]);
		}

		return 0;
	}
	return 0;
}

int rxUART(int uart0_filestream, char message[messageLength]){
//----- CHECK FOR ANY RX BYTES -----
	//if (uart0_filestream != -1)
	//{
    for(int i=0; i<20; i++){    //wait 2 sec for response
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
			if(verify){
				printf("%i bytes read :\n", rx_length);
				for(int i=0; i<rx_length;i++)
                    printf("message[%d]: %d\n",i, rx_buffer[i]);
			}
			return checkRecivedMessage(rx_buffer, message);
		}
        usleep(50000);
	}
    printf("No return from message!\n");
    return ERROR_NO_RETURN_MESSAGE;
}

int txUART(int uart0_filestream, char message[messageLength]){
	
	if (uart0_filestream != -1){
		int count = write(uart0_filestream, &message[0], messageLength);		//Filestream, bytes to write, number of bytes to write
		if (count < 0){
		    printf("UART TX error\n");
            return ERROR_TXUART;
		}
        return rxUART(uart0_filestream, message);
	}
    return ERROR_TXUART_CLOSED;
}

int setupUART(int baud, char *port){
	int uart0_filestream = -1;
	uart0_filestream = open(port, O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
	if (uart0_filestream == -1){
	    printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
        return ERROR_OPEN_UART;
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
