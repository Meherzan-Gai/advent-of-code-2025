CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: fresh

fresh: fresh.o
	$(CC) $(CFLAGS) -o fresh fresh.o

fresh.o: fresh.c
	$(CC) $(CFLAGS) -c fresh.c

clean:
	rm -f *.o fresh