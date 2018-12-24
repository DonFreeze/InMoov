
all: uart

uart: uart.o main.o 
	gcc uart.o main.o -o uart

main.o: main.c uart.h
	gcc -c main.c

Uart.o: uart.h uart.c
	gcc -c uart.c

clean:
	$(RM) uart main.o uart.o
