CC = gcc
CFLAGS = -Wall -Wextra

all: program

program: main.o
	$(CC) $(CFLAGS) -o $@ $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o program
