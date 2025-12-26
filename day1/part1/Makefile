CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: locker

locker: locker.o
	$(CC) $(CFLAGS) -o locker locker.o

locker.o: locker.c
	$(CC) $(CFLAGS) -c locker.c

clean:
	rm -f *.o locker