#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int** generate_grid(int m, int n){
    int** grid = malloc(m * sizeof(int*)); // miejsce dla wierszy

    if(!grid){
        fprintf(stderr, "Błąd alokaji pamięci dla wierszy.");
        return NULL;
    }

    for(int row = 0; row < m; row++){
        grid[row] = malloc(n*sizeof(int));
        if(!grid[row]){
            fprintf(stderr, "Błąd alokaji pamięci dla kolumny: %d.", row);
            free(grid);
            return NULL;
        }

        for(int col = 0; col < n; col++){
            grid[row][col] = 1;
        }
    }

    return grid;
    }



void print_maze(int** maze, int m, int n){
    for(int i=0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(maze[i][j] == 0){
                printf(" ");
            }
            if(maze[i][j] == 1){
                printf("#");
            }
        }
        printf("\n");
    }
}


// zwolnienie pamięci
void free_grid(int** grid, int m){
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
}