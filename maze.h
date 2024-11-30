#ifndef _MAZE_H_
#define _MAZE_H_


//generownaie szkieletu labiryntu
int** generate_grid(int m, int n);

void print_maze(int** maze, int m, int n);


void free_grid(int** grid, int m);
#endif