CC = gcc
CFLAGS = -Wall -Wextra

all: main

main: main.o normal_mode.o command_mode.o file_operations.o
	$(CC) $(CFLAGS) -o main main.o normal_mode.o command_mode.o file_operations.o

main.o: main.c normal_mode.h command_mode.h
	$(CC) $(CFLAGS) -c main.c

normal_mode.o: normal_mode.c normal_mode.h file_operations.h
	$(CC) $(CFLAGS) -c normal_mode.c

command_mode.o: command_mode.c command_mode.h file_operations.h
	$(CC) $(CFLAGS) -c command_mode.c

file_operations.o: file_operations.c file_operations.h
	$(CC) $(CFLAGS) -c file_operations.c

clean:
	rm -f *.o main
