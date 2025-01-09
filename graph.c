#include <stdio.h>
#include <stdlib.h>
#include <float.h> // dla DBL_MAX (nieskończoność)
#include "cell.h"
#include "graph.h"
#define INF DBL_MAX

// Tworzenie macierzy sąsiedztwa
void create_adjacency_matrix(cell_t** grid, int m, int n, double** matrix) {
    int total_vertices = m * n;

    // Inicjalizacja macierzy sąsiedztwa
    for (int i = 0; i < total_vertices; i++) {
        for (int j = 0; j < total_vertices; j++) {
        matrix[i][j] = (i == j) ? 0.0 : INF; //INF będzie dla nas oznaczać brak przejścia (nieskończony koszt przejścia)
        }
    }


    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int current = i * n + j;

            // Góra
            if (grid[i][j].walls[0] == 0 && i > 0) { 
                int neighbor = (i - 1) * n + j;
                matrix[current][neighbor] = grid[i-1][j].value;
                matrix[neighbor][current] = grid[i][j].value; 
            }
            // Prawo
            if (grid[i][j].walls[1] == 0 && j < n - 1) {
                int neighbor = i * n + (j + 1);
                matrix[current][neighbor] = grid[i][j+1].value;
                matrix[neighbor][current] = grid[i][j].value; 
            }
            // Dół
            if (grid[i][j].walls[2] == 0 && i < m - 1) {
                int neighbor = (i + 1) * n + j;
                matrix[current][neighbor] = grid[i+1][j].value;
                matrix[neighbor][current] = grid[i][j].value; 
            }
            // Lewo
            if (grid[i][j].walls[3] == 0 && j > 0) {
                int neighbor = i * n + (j - 1);
                matrix[current][neighbor] = grid[i][j-1].value;
                matrix[neighbor][current] = grid[i][j].value; 
            }
        }
    }
}


double** allocate_matrix(int size){
    //pamięć na wskaźniki do wierszy
    double** matrix = (double**)malloc(size * sizeof(double*));
    if (matrix == NULL) {
        perror("Nie udało się zaalokować pamięci na wskaźniki do wierszy.");
        return NULL;
    }

    //pamięć na kolumny dla każdego wiersza
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
        if (matrix[i] == NULL) {
            perror("Nie udało się zaalokować pamięci na kolumny.");
            return NULL;
        }
    }

    return matrix;
}



void print_matrix(double** matrix, int size) {
    printf("Macierz sąsiedztwa (%d x %d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == DBL_MAX) {
                printf("    -    "); // nieprzystające
            } else {
                printf("%8.2f ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}