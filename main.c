#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
//random maze gnerator depth first search


//na początku generuje pełną planszę (siatkę o podanym wymiarze)


typedef enum {up, right, down, left} direction_t; //definicja rodzajów kierunków


//sprawdzanie czy komórka jest w granicach labiryntu
int is_valid_cell(int m, int n, int row, int col, direction_t d){
        switch(d){
        case up: return row - 1 > 0 ? 1 : 0;
        break;
        case down: return row + 1 < m ? 1 : 0;
        break;
        case right: return col + 1 < n ? 1 : 0;
        break;
        case left: return  col - 1 > 0 ? 1 : 0;
        break; 
        default : return 0;
    }
}

//Fisher-Yates Shuffle
//losowa zmiana kolejności w tablicy kierunków, aby wybierać sąsiadów w DFS losowo
void shuffle(direction_t arr[]){
    srand(time(NULL)); //losowe ziarno generatora liczb losowych

    for(int i = 0; i < 4; i++){
        int j = i + rand() % (4-i);

        direction_t temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }    
}


int** visited_init(int m, int n){
    int** arr = malloc(m * sizeof(int*));
    for(int i=0; i < m; i++){
    arr[i] = malloc(n * sizeof(int));
    if(!arr[i]){
        fprintf(stderr, "Błąd alokacji pamięci dla tablicy visited.\n");
        return NULL;
    }
    for(int j = 0; j < n; j++){
        arr[i][j] = 0;
    }
    }
    return arr;
}


int main(int argc, char **argv){
    //pobieranie m i n oraz podstawowe wartosci w przypadku braku podania przy wywolaniu
    int m = argc > 1 ? atoi(argv[1]) : 10;
    int n = argc > 2 ? atoi(argv[2]) : m;
 
    int** grid = generate_grid(m, n);
    if(!grid){
        return EXIT_FAILURE;
    }


    //inicializacja tablicy visited, bazowo wszytkie komórki nie odwiedzone
    //deklaracja możliwych kierunków
    int** visited = visited_init(m, n);
    int directions[] = {up, right, down, left}; 


    //tworzenie otworów wejściowego (lewy górny) i końcowego (prawy dolny)
    grid[0][1] = 0;
    grid[m-1][n-2] = 0;

    visited[0][1] = 0;
    visited[m-1][n-2] = 0;


    //DFS

    


    //test generowania szkieletu labiryntu
    print_maze(grid, m, n);
    free_grid(grid, m);
    return EXIT_SUCCESS;

}