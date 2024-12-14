a.out: main.o maze.o graph.o
	gcc -Wall -pedantic main.o maze.o graph.o

main.o: main.c maze.h graph.h
	gcc -c -Wall -pedantic main.c

maze.o: maze.c maze.h
	gcc -c -Wall -pedantic maze.c

graph.o: graph.h graph.c
	gcc -c -Wall -pedantic graph.c
