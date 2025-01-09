a.out: main.o maze.o graph.o path.o
	gcc -Wall -pedantic -Wextra main.o maze.o graph.o path.o

main.o: main.c maze.o graph.o path.o
	gcc -c -Wall -pedantic main.c 

maze.o: maze.c maze.h
	gcc -c -Wall -pedantic maze.c

graph.o: graph.h graph.c
	gcc -c -Wall -pedantic graph.c

path.o: path.c path.h
	gcc -c -Wall -pedantic path.c
