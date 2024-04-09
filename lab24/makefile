all: main

main: main.o tree.o stack.o
	gcc -g main.o tree.o stack.o -o main

main.o: main.c tree.h stack.h
	gcc -g main.c -c -o main.o

tree.o: tree.c tree.h stack.h
	gcc -g tree.c -c -o tree.o
stack.o: stack.c stack.h
	gcc -g stack.c -c -o stack.o
clean:
	rm tree.o stack.o main.o