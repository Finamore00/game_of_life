#include <stdio.h>
#include <stdlib.h>
#include "../header_files/constants.h"
#include "../header_files/client_utils.h"
#include "../header_files/input_utils.h"

/**
 * Implementation in C of John Conway's Game of Life. Small
 * project to practice multithreaded programming and graphics
 * display in C using the SDL2 library.
 * 
 * Author: Santiago Finamore (Finamore00)
 * April, 2024
*/
int main(int argc, char *argv[]) {
    int work_grid[GRID_HEIGHT][GRID_WIDTH];
    int ref_grid[GRID_HEIGHT][GRID_WIDTH];

    //Initialize work and reference grids
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            work_grid[i][j] = 0;
            ref_grid[i][j] = 0;
        }
    }

    //Read command line arguments and determine operation mode.
    cmd_parse_res *parse_res = parse_cmd_line_arguments(argc, argv);

    //Get errors out of the way
    if (parse_res->status == CMD_FMT_ERR) {
        print_cmd_args_err_msg();
        return 1;
    }

    if (parse_res->status == HELP_MODE) {
        print_help();
        return 0;
    }

    if (parse_res->status == WRITE_MODE) {
        int write_res = generate_input_file(parse_res->file_path);
        switch (write_res) {
            case WRITE_FILE_ERR:
                printf("An error occured when writing to file.\n");
                return 1;
            case FILE_CREATION_ERR:
                printf("An error occured when creating the new file.\n");
                return 1;
            case FILE_ALREADY_EXISTS_ERR:
                printf("There's already a file in the specified path.\n");
                return 1;
            case FILE_CREATION_SUCCESS:
                printf("The input file has been created successfully.\n");
                return 1;
            default:
                printf("An unknown error happened.\n");
                return 1;
        }
        return 0;
    }

    if (parse_res->status == READ_MODE) {
        int read_res = read_input_file(parse_res->file_path, work_grid);
        switch (read_res) {
            case FILE_ACCESS_ERR:
                printf("An error occured when opening the specified file.\n");
                return 1;
            case FILE_READ_ERR:
                printf("An error occured when reading from the file.\n");
                return 1;
            case FILE_READ_SUCCESS:
                break;
            default:
                printf("Unknown error occured when reading file.\n");
                return 1;
        }
    }

    /*TO-DO Normal mode (randomly generated matrix)*/

    

    free_cmd_parse_res(parse_res);

    return 0;
}