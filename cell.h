#include "direction.h"

#ifndef _CELL_H_

#define _CELL_H_


typedef struct{
    int walls[4]; //up, right, down, left
    double value;
    int is_visited;
} cell_t;


#endif

