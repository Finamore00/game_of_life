#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "../header_files/constants.h"
#include "../header_files/client_utils.h"
#include "../header_files/input_utils.h"
#include "../header_files/game_funcs.h"
#include "../header_files/SDL_utils.h"

/**
 * Implementation in C of John Conway's Game of Life. Small
 * project to practice multithreaded programming and graphics
 * display in C using the SDL2 library.
 * 
 * Author: Santiago Finamore (Finamore00)
 * April, 2024
*/
int main(int argc, char *argv[]) {

    //SDL-related declarations and initializations
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(GRID_WIDTH * 10, GRID_HEIGHT * 10, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);


    //Game logic declarations and initialization
    bool quit_flag = false;
    pthread_attr_t attr;
    pthread_t threads[4]; //Add argument for indicating thread count later.
    update_subgrid_struct *args[4];
    int work_grid[GRID_HEIGHT][GRID_WIDTH];
    int ref_grid[GRID_HEIGHT][GRID_WIDTH];

    for (int i = 0; i < 4; i++) {
        args[i] = (update_subgrid_struct *)malloc(sizeof(update_subgrid_struct));

        if (i%2 == 0) {
            args[i]->y0 = 0;
            args[i]->yf = GRID_HEIGHT / 2;
            args[i]->x0 = i == 0 ? 0 : GRID_WIDTH / 2;
            args[i]->xf = i == 0 ? GRID_WIDTH / 2 : GRID_WIDTH;
        } else {
            args[i]->y0 = GRID_HEIGHT / 2;
            args[i]->yf = GRID_HEIGHT;
            args[i]->x0 = i == 1 ? 0 : GRID_WIDTH / 2;
            args[i]->xf = i == 1 ? GRID_WIDTH / 2 : GRID_WIDTH;
        }

        args[i]->work_grid = work_grid;
        args[i]->ref_grid = ref_grid;
    }

    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            work_grid[i][j] = 0;
            ref_grid[i][j] = 0;
        }
    }

    pthread_attr_init(&attr);

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
    } else {
        generate_random_grid(work_grid);
    }

    do {
        clear_display(renderer);

        memcpy(ref_grid, work_grid, sizeof(int) * GRID_HEIGHT * GRID_WIDTH);
        for (int i = 0; i < 4; i++) {
            int tr = pthread_create(&threads[i], &attr, update_subgrid, (void *)args[i]);
            if (tr) {
                printf("Error occured when spawning thread. Exiting.\n");
                exit(1);
            }
        }

        for (int i = 0; i < 4; i++) {
            pthread_join(threads[i], NULL);
        }

        display_grid(renderer, work_grid);
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit_flag = true;
            }
        }
        usleep(DELTA_T * 1000);

    } while (!quit_flag);

    //Heap clean-up
    for (int i = 0; i < 4; i++) {
        free(args[i]);
    }

    pthread_attr_destroy(&attr);
    free_cmd_parse_res(parse_res);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}