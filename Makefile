CC=gcc
CFLAGS=-I.
DEPS = operations.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o operations.o 
	$(CC) -o main main.o operations.o 