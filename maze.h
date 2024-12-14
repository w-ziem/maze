#include "cell.h"
#include "direction.h"
#ifndef _MAZE_H_
#define _MAZE_H_


cell_t** generate_grid(int m, int n);

void print_maze(cell_t** maze, int m, int n);

void free_grid(cell_t** grid, int m);

int is_valid_cell(cell_t** grid, int m, int n, int row, int col);

void remove_wall(cell_t* current, cell_t* next, direction_t d);

double get_rand(double min, double max);

void generate_paths(cell_t** grid, int m, int n, direction_t *directions, int i, int j);

void ensure_full_coverage(cell_t** grid, int m, int n, direction_t *directions);

void shuffle(direction_t arr[]);

#endif