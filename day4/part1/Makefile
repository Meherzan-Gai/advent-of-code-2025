CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: forklift

forklift: forklift.o
	$(CC) $(CFLAGS) -o forklift forklift.o

forklift.o: forklift.c
	$(CC) $(CFLAGS) -c forklift.c

clean:
	rm -f *.o forklift