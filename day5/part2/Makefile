CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: fresh2

fresh2: fresh2.o
	$(CC) $(CFLAGS) -o fresh2 fresh2.o

fresh2.o: fresh2.c
	$(CC) $(CFLAGS) -c fresh2.c

clean:
	rm -f *.o fresh2