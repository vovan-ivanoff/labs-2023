CC=gcc -g -Wall -std=99c -pedantic
all: main
default: main

main: main.o list.o
	gcc main.o list.o -o main

main.o: main.c list.h
	gcc main.c -c -o main.o 

list.o: list.c list.h
	gcc list.c -c -o list.o

clean: 
	rm -rf main.o list.o