#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include <assert.h>
//random maze gnerator depth first search


//Fisher-Yates Shuffle
//losowa zmiana kolejności w tablicy kierunków, aby wybierać sąsiadów w DFS losowo
void shuffle(direction_t arr[]){

    for(int i = 0; i < 4; i++){
        int j = i + rand() % (4-i);

        direction_t temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }    
    // printf("Shuffled directions: {%d, %d, %d, %d}\n", arr[0], arr[1], arr[2], arr[3]);
}


void generuj_sciezki(cell_t** grid, int m, int n, direction_t *directions, int i, int j, int visited_counter){
    //i,j są lokalizacją aktualnej komróki

    if(visited_counter == m*n){
        return;
    }

    //mieszanie kierunków aby labirynt był losowy
    shuffle(directions);


    for(int d = 0; d < 4; d++){
        int next_i = i;
        int next_j = j;
        switch (directions[d]) {
                case up:    next_i = i - 1; break;
                case down:  next_i = i + 1; break;
                case left:  next_j = j - 1; break;
                case right: next_j = j + 1; break; 
            }
        //logi do debuggowania
        // printf("Aktualna komórka: (%d, %d), odwiedzone: %d\n", i, j, visited_counter);
        // printf("Kierunek: %d, nowa komórka: (%d, %d)\n", directions[d], next_i, next_j);
        //     printf("Current state\n");
        //     print_maze(grid, m, n, i, j, next_i, next_j);


        //sprawdzanie, czy komórka jest odwiedzona oraz w granicach
        if(is_valid_cell(grid, m, n, next_i, next_j)){
            //debug
            // printf("valid cell (%d, %d)\n", next_i, next_j);
            remove_wall(&grid[i][j], &grid[next_i][next_j], directions[d]);

            //oznaczanie komórki jako odwiedzonej
            grid[next_i][next_j].is_visited = 1;
            visited_counter++;
            //rekurencja dla nowej komórki
            generuj_sciezki(grid, m, n, directions, next_i, next_j, visited_counter);
            // brute force backtrack, aby została sprawdzona każda komórka
            for(int new_d = 0; new_d < 4; new_d++){
                next_i = i;
                next_j = j;
                switch (directions[new_d]) {
                        case up:    next_i = i - 1; break;
                        case down:  next_i = i + 1; break;
                        case left:  next_j = j - 1; break;
                        case right: next_j = j + 1; break; 
                    }
                generuj_sciezki(grid, m, n, directions, next_i, next_j, visited_counter);
            }
        }
    }

}

int main(int argc, char **argv){
    srand(time(NULL)); //losowe ziarno generatora liczb losowych
    //pobieranie m i n oraz podstawowe wartosci w przypadku braku podania przy wywolaniu
    int m = argc > 1 ? atoi(argv[1]) : 10;
    int n = argc > 2 ? atoi(argv[2]) : m;
 
    cell_t** grid = generate_grid(m, n);
    if(!grid){
        return EXIT_FAILURE;
    }

    //deklaracja możliwych kierunków
    direction_t directions[] = {up, right, down, left}; 

    //tworzenie otworów wejściowego (lewy górny) i końcowego (prawy dolny)
    grid[0][1].walls[0] = 0;
    grid[m-1][n-2].walls[2] = 0;
    grid[0][1].is_visited = 1;  


    generuj_sciezki(grid, m, n, directions, 0, 1, 1);
    print_maze(grid, m, n);
    free_grid(grid, m);
    return EXIT_SUCCESS;

}