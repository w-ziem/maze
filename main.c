#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
//random maze gnerator depth first search


//na początku generuje pełną planszę (siatkę o podanym wymiarze)


int main(int argc, char **argv){
    //pobieranie m i n oraz podstawowe wartosci w przypadku braku podania przy wywolaniu
    int m = argc > 1 ? argv[0] : 10;
    int n = argc > 2 ? argv[1] : m;
 
    int* grid[] = generate_grid(2, 3);
    if(!grid){
        return EXIT_FAILURE;
    }

    //test generowania szkieletu labiryntu
    print_maze(grid, m, n);

}