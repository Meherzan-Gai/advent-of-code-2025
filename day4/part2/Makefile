CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: forklift2

forklift2: forklift2.o
	$(CC) $(CFLAGS) -o forklift2 forklift2.o

forklift2.o: forklift2.c
	$(CC) $(CFLAGS) -c forklift2.c

clean:
	rm -f *.o forklift2