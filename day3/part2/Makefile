CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: voltage2

voltage2: voltage2.o
	$(CC) $(CFLAGS) -o voltage2 voltage2.o

voltage2.o: voltage2.c
	$(CC) $(CFLAGS) -c voltage2.c

clean:
	rm -f *.o voltage2