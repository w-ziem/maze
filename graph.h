#include "cell.h"

#ifndef _GRAPH_H_
#define _GRAPH_H_

void create_adjacency_matrix(cell_t** grid, int m, int n, double** matrix);

double** allocate_matrix(int size);

void print_matrix(double** matrix, int size);

#endif