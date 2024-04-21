#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../header_files/constants.h"

#define WRITE_FILE_ERR -1
#define FILE_ALREADY_EXISTS_ERR -2
#define FILE_CREATION_ERR -3
#define FILE_CREATION_SUCCESS 0
#define FILE_ACCESS_ERR -1
#define FILE_READ_ERR -2
#define FILE_READ_SUCCESS 0

int generate_input_file(const char *file_path) {

    if (access(file_path, F_OK) == 0) {
        return FILE_ALREADY_EXISTS_ERR;
    }

    FILE *fptr = fopen(file_path, "w");
    if (fptr == NULL) {
        return FILE_CREATION_ERR;
    }

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            int value = rand() % 100 < 70 ? 0 : 1;
            if (fprintf(fptr, "%d ", value) < 0) {
                fclose(fptr);
                return WRITE_FILE_ERR;
            }
        }

        if (fprintf(fptr, "\n") < 0) {
            fclose(fptr);
            return WRITE_FILE_ERR;
        }
    }

    fclose(fptr);
    return FILE_CREATION_SUCCESS;
    
}

int read_input_file(char *file_path, int (*grid)[GRID_WIDTH]) {
    if (access(file_path, F_OK) != 0) {
        return FILE_ACCESS_ERR;
    }

    FILE *fptr = fopen(file_path, "r");

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (fscanf(fptr, "%d ", &grid[i][j]) < 0) {
                return FILE_READ_ERR;
            }
        }
    }

    fclose(fptr);

    return FILE_READ_SUCCESS;
}

void generate_random_grid(int (*grid)[GRID_WIDTH]) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            int value = rand() % 100 > 70 ? 1 : 0;
            grid[i][j] = value;
        }
    }
}