CC = gcc
CFLAGS = -Wall -Wextra

all: diccionario

diccionario: main.o
	$(CC) $(CFLAGS) -o $@ $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o 
