CC = gcc
CFLAGS = -fno-stack-protector -no-pie -Wall

%.o:
	$(CC) $(CFLAGS) -o $*.o -c $*.c

main: main.o
	$(CC) $(CFLAGS) -o $@ $^

all: main

clean:
	rm -f *.o main