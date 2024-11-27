#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
//random maze gnerator depth first search


//na początku generuje pełną planszę (siatkę o podanym wymiarze)


int main(int argc, char **argv){
    //TODO: pobieranie m i n oraz podstawowe wartosci w przypadku braku podania przy wywolaniu
    int* grid[] = generate_grid(m, n);
    if(!grid){
        return EXIT_FAILURE;
    }

}