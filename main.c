#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "graph.h"
#include "path.h"
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
    int start_index = 0;
    int end_index = m * n - 1;


    //tworzenie ścieżek zaczynając od komórki wejściowej
    generate_paths(grid, m, n, directions, 0, 0);

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

    //szukanie najktórszej ścieżki
    printf("Szukanie najkrószej ścieżki...\n");
    int* shortest_path = malloc(m*n * sizeof(int));
    int path_length;
    find_shortest_path(matrix, m * n, start_index, end_index, shortest_path, &path_length);

    print_shortest_path(matrix, n, shortest_path, path_length); 

    free_grid(grid, m);
    return EXIT_SUCCESS;

} 