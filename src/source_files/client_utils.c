#include "../header_files/constants.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_FMT_ERR -1
#define NORMAL_MODE 0
#define WRITE_MODE 1
#define READ_MODE 2
#define HELP_MODE 3

typedef struct cmd_parse_res {
    int status;
    char *file_path;
} cmd_parse_res;

void free_cmd_parse_res(cmd_parse_res *ptr) {
    free(ptr->file_path);
    free(ptr);
}

cmd_parse_res *parse_cmd_line_arguments(int argc, char *argv[]) {

    cmd_parse_res *result = (cmd_parse_res*)malloc(sizeof(cmd_parse_res));
    result->status = CMD_FMT_ERR;
    result->file_path = NULL;

    
    if (argc == 1) {
        result->status = NORMAL_MODE;
        result->file_path = NULL;
    } else if (argc == 2) {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            result->status = HELP_MODE;
            result->file_path = NULL;
        } else {
            result->status = READ_MODE;
            size_t path_len = strlen(argv[1]) + 1; //Make space for trailing \0
            result->file_path = (char *)malloc(path_len * sizeof(char));
            strncpy(result->file_path, argv[1], path_len);
            result->file_path[path_len - 1] = '\0';
        }
    } else if (argc == 3) {
        if (!strcmp(argv[1], "-c") || !strcmp(argv[1], "--create")) {
            result->status = WRITE_MODE;
            size_t path_len = strlen(argv[2]) + 1; //Make space for trailing \0
            result->file_path = (char *)malloc(path_len * sizeof(char));
            strncpy(result->file_path, argv[2], path_len);
            result->file_path[path_len - 1] = '\0';
        }
    }

    return result;
}

void print_help() {
    printf("PROGRAM USSAGE:\n");
    printf("\tGameOfLife [FLAG] [FILE_PATH]\n");
    printf("GameOfLife <FILE_PATH> Executes the game using the initial grid specified in the input file located at FILE_PATH\n");
    printf("Calling the program with no arguments will run the game with a randomized board\n");
    printf("FLAGS:\n");
    printf("\t-c, --create: Creates a randomized input file in the specified FILE_PATH\n");
    printf("\t-h, --help: Outputs program manual\n");
}

void print_cmd_args_err_msg() {
    printf("Inputted command is invalid or incorrectly formatted.\n");
    printf("For program manual, invoke using the --help flag.\n");
}