#ifndef _PATH_H_
#define _PATH_H_
#include "cell.h"

void find_shortest_path(double** matrix, int size, int start, int end, int* path, int* path_lenght);
void ensure_start_end_connectivity(cell_t** grid, int m, int n, double** matrix);
void print_shortest_path(double** matrix, int n, int* shortest_path, int path_length);

#endif
