CC=gcc -g -Wall -std=c99 -pedantic
all: main
default: main
main: main.o table.o sort.o
	gcc main.o table.o sort.o -o main

sort.o: sort.c sort.h
	gcc sort.c -c -o sort.o

table.o: table.c table.h
	gcc table.c -c -o table.o

clean: 
	rm -rf main.o table.o sort.o