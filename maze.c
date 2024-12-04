#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "cell.h"

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
            }
        }
    }

    return grid;
    }


// void print_maze(cell_t** maze, int m, int n){
//     for(int i=0; i < m; i++){
//         for(int j = 0; j < n; j++){
//             if(maze[i][j].is_visited == 0){
//                 printf(" ");
//             }
//             if(maze[i][j].is_visited == 1){
//                 printf("#");
//             }
//         }
//         printf("\n");
//     }
// }


void print_maze(cell_t** grid, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Drukowanie górnych ścian
            printf(grid[i][j].walls[0] ? "###" : "#  ");
        }
        printf("#\n");

        for (int j = 0; j < n; j++) {
            // Drukowanie bocznych ścian i komórek
            printf(grid[i][j].walls[3] ? "#" : " ");
            printf("   ");
        }
        printf("#\n");
    }

    // Drukowanie dolnej krawędzi
    for (int j = 0; j < n; j++) {
        printf("###");
    }
    printf("#\n");
}

//sprawdzanie czy komórka jest w granicach labiryntu
int is_valid_cell(cell_t** grid, int m, int n, int row, int col) {
    return row >= 0 && row < m && col >= 0 && col < n && !grid[row][col].is_visited;
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


//FIXME: wersja na liste dwuwymiarową, trzeba przerobić na Cell
// zwolnienie pamięci
void free_grid(cell_t** grid, int m){
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
}