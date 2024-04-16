all: main

main: main.o util.o queue.o
	gcc main.o util.o queue.o -o main

main.o: main.c util.h queue.h
	gcc main.c -c -o main.o

util.o: util.c util.h queue.h
	gcc util.c -c -o util.o
queue.o: queue.c queue.h
	gcc queue.c -c -o queue.o
clean:
	rm util.o queue.o main.o main