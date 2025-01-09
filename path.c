#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include <float.h>
#define INF DBL_MAX //nieskończoność


void find_shortest_path(double** matrix, int size, int start, int end, int* path, int* path_length){
    
    double* dist = malloc(size * sizeof(double)); //całkowity koszt dotarcia do tego wierzchołka
    int* prev = malloc(size * sizeof(int)); //z jakiego wierzchołka przeszliśmy do aktualnego
    int* visited = malloc(size * sizeof(int)); //które wierzchołki były już odwiedzone

    for(int i = 0; i < size; i++){
        dist[i] = INF; // na początek wszystkie dystanse ustawiam na nieskończoność
        prev[i] = -1; //oznaczenie, że to początek - nie ma takiego indexu
        visited[i] = 0; //0 uznaje za fałsz, liczbę (1) za prawdę
    }

    dist[start] = 0; //zaczynamy ze startu, więc przejście na start nie kosztuje
    
    //eklsporowania każdej możliwej ścieżki - Dijkstra's algorithm
    for(int i = 0 ; i < size; i++){
        int min_vertex = -1;
        double min_dist = INF;
        for(int j=0; j< size; j++){
            if(visited[j] == 0 && dist[j] < min_dist) {
                min_vertex = j;
                min_dist = dist[j];
            }
        }

    if(min_vertex == -1) break;
    visited[min_vertex] = 1;
    //sprawdzanie wszystkich sąsiednich wierzchołków
    for(int j=0; j < size; j++){
        if(visited[j]==0 && matrix[min_vertex][j] != INF && dist[min_vertex] != INF){
            double new_dist = dist[min_vertex] + matrix[min_vertex][j];
            if (new_dist < dist[j]) {
                dist[j] = new_dist;
                prev[j] = min_vertex;
            }
        }
    }
    }
    
    // znajdywanie ściezki od początku do końca
    int curr = end;
    *path_length = 0;
    while(curr != -1){
        path[(*path_length)++] = curr;
        //sprawdzianie połącznia wierzchołków
        if (prev[curr] != -1 && matrix[prev[curr]][curr] == INF) {
            fprintf(stderr, "Błąd: Brak połączenia między wierzchołkami w rekonstrukcji ścieżki.\n");
            *path_length = 0; // Oznaczamy, że ścieżka nie została znaleziona
            free(dist);
            free(prev);
            free(visited);
            return;
        }
        curr = prev[curr];
    }    
    // odwracanie ścieżki
    for(int i = 0; i < *path_length/2; i++) {
        int temp = path[i];
        path[i] = path[*path_length-1-i];
        path[*path_length-1-i] = temp;
    }

    if(dist[end] == INF) {
        printf("Brak ściezki.\n");
    }
    printf("Najkrótsza śieżka: %.2f\n", dist[end]);
    free(dist);
    free(prev);
    free(visited);
}

void print_shortest_path(double** matrix, int n, int* shortest_path, int path_length) {
    printf("Najkrótsza ścieżka: ");
    if (path_length == 0) {
        printf("Brak ścieżki\n");
        return;
    }
    for (int i = 0; i < path_length; i++) {
        int x = shortest_path[i] / n;
        int y = shortest_path[i] % n;
        printf("(%d,%d)", x, y);
        if (i < path_length - 1) {
            int next_x = shortest_path[i+1] / n;
            int next_y = shortest_path[i+1] % n;
            if (matrix[shortest_path[i]][shortest_path[i+1]] == INF){
                printf(" -> (BŁĄD: Brak połączenia z (%d,%d))", next_x, next_y);
            } else {
                printf(" -> ");
            }
        }
    }
    printf("\n");
}