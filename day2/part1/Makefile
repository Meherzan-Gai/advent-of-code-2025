CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all

.PHONY: all clean backup

all: invalid

invalid: invalid.o
	$(CC) $(CFLAGS) -o invalid invalid.o

invalid.o: invalid.c
	$(CC) $(CFLAGS) -c invalid.c

clean:
	rm -f *.o invalid