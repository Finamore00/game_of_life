#ifndef GAME_OF_LIFE_GAME_FUNCS_H

//Idk why it was whining in this file specifically but I have to inlcude the constants I guess.
#include "constants.h"

typedef struct update_subgrid_struct {
    int (*work_grid)[GRID_WIDTH];
    int (*ref_grid)[GRID_WIDTH];
    int x0;
    int y0;
    int xf;
    int yf;
} update_subgrid_struct;

void update_point(int x, int y, int (*work_grid)[GRID_WIDTH], int (*ref_grid)[GRID_WIDTH]);
void *update_subgrid(void *args_void);
void print_grid(int (*grid)[GRID_WIDTH]);

#define GAME_OF_LIFE_GAME_FUNCS_H
#endif