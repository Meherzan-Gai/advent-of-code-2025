CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: locker2

locker2: locker2.o
	$(CC) $(CFLAGS) -o locker2 locker2.o

locker2.o: locker2.c
	$(CC) $(CFLAGS) -c locker2.c

clean:
	rm -f *.o locker2