
all: uart

uart: Uart.o main.o 
	gcc Uart.o main.o -o uart

main.o: main.cpp Uart.hpp
	gcc -c main.cpp

Uart.o: Uart.hpp Uart.cpp
	gcc -c Uart.cpp

clean:
	$(RM) uart main.o Uart.o
