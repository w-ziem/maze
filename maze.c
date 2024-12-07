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

// wyświetlanie budowania się labiryntu
void print_maze(cell_t** grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        // Górne ściany
        for (int j = 0; j < cols; j++) {
            printf("+");
            if (grid[i][j].walls[0] == 1)
                printf("---");  // Górna ściana
            else
                printf("   ");  // Brak górnej ściany
        }
        printf("+\n");

        // Boki komórki i wnętrze
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].walls[3] == 1)
                printf("|");  // Lewa ściana
            else
                printf(" ");  // Brak lewej ściany

            // debug log [, int ci, int cj, int ni, int nj]
            // if(i == ci &&  j == cj){
            //     printf("cur");
            // } else if(i==ni && j == nj){
            //     printf("nxt");
            // } else{
            //     printf("   "); // Wnętrze komórki (można zmodyfikować, np. dodać treść)
            // }
            printf("   ");
        }
        printf("|\n");  // Prawa ściana na końcu wiersza
    }

    // Dolne ściany ostatniego wiersza
    for (int j = 0; j < cols; j++) {
        printf("+");
        if (grid[rows - 1][j].walls[2] == 1)
            printf("---");  // Dolna ściana
        else
            printf("   ");  // Brak dolnej ściany
    }
    printf("+\n");
}

//sprawdzanie czy komórka jest w granicach labiryntu
int is_valid_cell(cell_t** grid, int m, int n, int row, int col) {
    return row >= 0 && row < m  && col >= 0 && col < n  && grid[row][col].is_visited==0;
}


//usuwanie ścian między komórkami
void remove_wall(cell_t* current, cell_t* next, direction_t dir) {
    switch (dir) {
        case up:
            current->walls[0] = 0;
            next->walls[2] = 0;
            // printf("Usunąlem gorna sciane dla cur i dolna dla nxt\n");
            break;
        case right:
            current->walls[1] = 0;
            next->walls[3] = 0;
            //deug log
            // printf("Usunąlem prawa sciane dla cur i lewa dla nxt\n");
            break;
        case down:
            current->walls[2] = 0;
            next->walls[0] = 0;
            //deug log
            // printf("Usunąlem dolna sciane dla cur i gorna dla nxt\n");
            break;
        case left:
            current->walls[3] = 0;
            next->walls[1] = 0;
            //deug log
            // printf("Usunąlem lewa sciane dla cur i prawa dla nxt\n");
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