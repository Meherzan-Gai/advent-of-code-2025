CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: voltage

voltage: voltage.o
	$(CC) $(CFLAGS) -o voltage voltage.o

voltage.o: voltage.c
	$(CC) $(CFLAGS) -c voltage.c

clean:
	rm -f *.o voltage