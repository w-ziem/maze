#include "cell.h"
#ifndef _MAZE_H_
#define _MAZE_H_


//generownaie szkieletu labiryntu
cell_t** generate_grid(int m, int n);

void print_maze(cell_t** maze, int m, int n);

void free_grid(cell_t** grid, int m);

int is_valid_cell(cell_t** grid, int m, int n, int row, int col);

void remove_walls(cell_t* current, cell_t* next, direction_t d);


#endif