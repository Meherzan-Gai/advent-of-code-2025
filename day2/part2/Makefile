CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: invalid2

invalid2: invalid2.o
	$(CC) $(CFLAGS) -o invalid2 invalid2.o

invalid2.o: invalid2.c
	$(CC) $(CFLAGS) -c invalid2.c

clean:
	rm -f *.o invalid2
