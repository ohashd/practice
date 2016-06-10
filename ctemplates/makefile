CC = gcc
CFLAGS = -Wall -std=c99
OBJECTS = arrayint.o

array%.o: array%.c arraytemplate.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJECTS)
	$(CC) $(CFLAGS) main.c $(OBJECTS)

clean:
	del *.o