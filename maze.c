#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "cell.h"
#include "direction.h"


double get_rand(double min, double max){
    return min + ((double)rand() / RAND_MAX) * (max - min);
}



cell_t** generate_grid(int m, int n){

    cell_t** grid = malloc(m * sizeof(cell_t*)); // miejsce dla wierszy

    if(!grid){
        fprintf(stderr, "Błąd alokaji pamięci dla wierszy.");
        return NULL;
    }

    for(int row = 0; row < m; row++){
        grid[row] = malloc(n*sizeof(cell_t));
        if(!grid[row]){
            fprintf(stderr, "Błąd alokaji pamięci dla kolumny: %d.", row);
            free(grid);
            return NULL;
        }

        for(int col = 0; col < n; col++){
            grid[row][col].is_visited = 0;
            for(int k=0; k < 4; k++){
                grid[row][col].walls[k] = 1; //wszystkie sciany sa obecne
                grid[row][col].value = get_rand(0,10);
            }
        }
    }

    return grid;
    }



void print_maze(cell_t** grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        // Górne ściany
        for (int j = 0; j < cols; j++) {
            printf("+");
            if (grid[i][j].walls[0] == 1)
                printf("----");  // Górna ściana
            else
                printf("    ");  // Brak górnej ściany
        }
        printf("+\n");

        // Boki komórki i wnętrze
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].walls[3] == 1)
                printf("|");  // Lewa ściana
            else
                printf(" ");  // Brak lewej ściany
            if(rows*cols <= 15){
                printf("    "); //wyświetlania komórki jako pustego pola
            } else{
            printf("%.2f", grid[i][j].value); //wyświetlanie komórki z wartościami przejścia
            }

        }
        printf("|\n");  // Prawa ściana na końcu wiersza
    }

    // Dolne ściany ostatniego wiersza
    for (int j = 0; j < cols; j++) {
        printf("+");
        if (grid[rows - 1][j].walls[2] == 1)
            printf("----");  // Dolna ściana
        else
            printf("    ");  // Brak dolnej ściany
    }
    printf("+\n");
}

//sprawdzanie czy komórka jest w granicach labiryntu oraz nieodwiedzona
int is_valid_cell(cell_t** grid, int m, int n, int row, int col) {
    return row >= 0 && row < m  && col >= 0 && col < n  && grid[row][col].is_visited==0;
}


//usuwanie ścian między komórkami
void remove_wall(cell_t* current, cell_t* next, direction_t dir) {
    switch (dir) {
        case up:
            current->walls[0] = 0;
            next->walls[2] = 0;
            break;
        case right:
            current->walls[1] = 0;
            next->walls[3] = 0;
            break;
        case down:
            current->walls[2] = 0;
            next->walls[0] = 0;
            break;
        case left:
            current->walls[3] = 0;
            next->walls[1] = 0;
            break;
    }
}


// zwolnienie pamięci
void free_grid(cell_t** grid, int m){
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
}

//losowa zamiana kierunków aby wybierać losowego sąsiada
void shuffle(direction_t arr[]){

    for(int i = 0; i < 4; i++){
        int j = i + rand() % (4-i);

        direction_t temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }    
}





//tworzenie ścierzek, przejść
void generate_paths(cell_t** grid, int m, int n, direction_t *directions, int i, int j){
    //i,j są lokalizacją aktualnej komróki
    grid[i][j].is_visited = 1;

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

        //sprawdzanie, czy komórka jest odwiedzona oraz w granicach
        if(is_valid_cell(grid, m, n, next_i, next_j)){
            remove_wall(&grid[i][j], &grid[next_i][next_j], directions[d]);

            //oznaczanie komórki jako odwiedzonej
            grid[next_i][next_j].is_visited = 1;

            //rekurencja dla nowej komórki
            generate_paths(grid, m, n, directions, next_i, next_j);
        }
    }
}


// dla każdej nieodwiedzonej komórki wywołuje generowanie ścieżek, co zapobiega pominięciu niektórych komórek, szególnie przy dużych labiryntach
void ensure_full_coverage(cell_t** grid, int m, int n, direction_t *directions) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j].is_visited==0) {
                grid[i][j].walls[1] = 0;
                generate_paths(grid, m, n, directions, i, j);
            }
        }
    }
}


