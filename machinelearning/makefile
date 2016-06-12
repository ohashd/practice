OBJECTS = darray.o

%.o: %.c
	gcc -std=c99 -c -o $@ $< -Wall

default: ${OBJECTS}
	gcc -std=c99 main.c ${OBJECTS} -Wall
