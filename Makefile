a.out: main.o maze.o
	gcc -Wall -pedantic main.o maze.o

main.o: main.c maze.h
	gcc -c -Wall -pedantic main.c

maze.o: maze.c maze.h
	gcc -c -Wall -pedantic maze.c
