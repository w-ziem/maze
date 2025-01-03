#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "graph.h"
//random maze gnerator using recursive DFS


int main(int argc, char **argv){
    srand(time(NULL)); //losowe ziarno generatora liczb losowych
    
    //pobieranie m i n oraz podstawowe wartosci w przypadku braku podania przy wywolaniu
    int m = argc > 1 ? atoi(argv[1]) : 10;
    int n = argc > 2 ? atoi(argv[2]) : m;
 
    //generowanie "siatki" labiryntu (wszędzie są obecne ściany)
    cell_t** grid = generate_grid(m, n);
    if(!grid){
        return EXIT_FAILURE;
    }

    //deklaracja możliwych kierunków
    direction_t directions[] = {up, right, down, left}; 

    //tworzenie otworów wejściowego (lewy górny) i końcowego (prawy dolny)
    grid[0][0].walls[0] = 0;
    grid[m-1][n-1].walls[2] = 0;

    //tworzenie ścieżek
    ensure_full_coverage(grid, m, n, directions);
    //wyświetlanie labiryntu
    print_maze(grid, m, n);
    //alokacja pamięci dla macierzy 
    double** matrix = allocate_matrix(m*n);
    if(!matrix){
        return EXIT_FAILURE;
    }
    //tworzenie macierzy sąsiedztwa
    create_adjacency_matrix(grid, m, n, matrix);
    //wyświetlanie macierzy     
    if(n*m<=15){
        print_matrix(matrix, m*n);
    } else{
        printf("Macierz za duża aby wyświetlić (%d x %d)\n", n*m, m*n);
    }
    free_grid(grid, m);
    return EXIT_SUCCESS;

}