#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header_files/constants.h"

typedef struct update_subgrid_struct {
    int (*work_grid)[GRID_WIDTH];
    int (*ref_grid)[GRID_WIDTH];
    int x0;
    int y0;
    int xf;
    int yf;
} update_subgrid_struct;

void update_point(int x, int y, int (*work_grid)[GRID_WIDTH], int (*ref_grid)[GRID_WIDTH]) {
    //Count neighbors
    int live_neighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            //Don't check points out of bounds
            if (x + j >= 0 && x + j < GRID_WIDTH && y + i >= 0 && y + i < GRID_HEIGHT) {
                live_neighbors += ref_grid[i][j];
            }
        }
    }
    live_neighbors -= ref_grid[x][y]; //The point itself doesn't count as a neighbor

    //Update cell according to rules
    if (work_grid[x][y] == 1) {
        work_grid[x][y] = live_neighbors < 2 || live_neighbors > 3 ? 0 : 1;
    } else {
        work_grid[x][y] = live_neighbors == 3 ? 1 : 0;
    }
    return;
}

void *update_subgrid(void *args_void) {
    update_subgrid_struct *args = (update_subgrid_struct *)args_void;
    for (int i = args->y0; i < args->yf; i++) {
        for (int j = args->x0; j < args->xf; j++) {
            update_point(j, i, args->work_grid, args->ref_grid);
        }
    }
    pthread_exit(NULL);
}

void print_grid(int (*grid)[GRID_WIDTH]) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            printf(j == GRID_WIDTH - 1 ? "%d" : "%d, ", grid[i][j]);
            fflush(stdout);
        }
        printf("\n");
    }
}