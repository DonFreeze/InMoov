# PiArduino

This is the program running on the Raspberry Pi. It sends data to the Arduino and checks the acknowledge. The program is written in C.

## Getting Started

Usage: 
```
./uart [OPTION] . . .
```

Running the program without parameter will send a status message with standard options.
For status message see the Protocol.
Standard options for communication are:
* Baud: 9600
* Port: ttyAMA0

The message is send as hex, the maximum length is 8 byte. See the Protocol for more informations on how the message is build.
The message automatically contains a start ['S'] and end ['\n'] char which is not part of the actuall message.

### Example

```
./uart -m 2001010203
```
Will set the eye number 1 to mode 2 and color 3.
As specified in the Protocol.

### Parameter

The following parameter can be used:
```
-h 		Shows a help
-m message	message send to Arduino as hex, max Length is 8 byte
-b baudrate	Baudrate for the connection
-p port		USB Port Arduino is connected
-v 		More informations are displayed during run
```

### Installing

To compile the program just run the Makefile. To do so direct in this directory and use the command:
``` 
make
```

