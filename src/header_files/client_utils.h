#ifndef GAME_OF_LIFE_CLIENT_UTILS_H

#define CMD_FMT_ERR -1
#define NORMAL_MODE 0
#define WRITE_MODE 1
#define READ_MODE 2
#define HELP_MODE 3

typedef struct cmd_parse_res {
    int status;
    char *file_path;
} cmd_parse_res;

void free_cmd_parse_res(cmd_parse_res *ptr);
cmd_parse_res *parse_cmd_line_arguments(int argc, char *argv[]);
void print_help();
void print_cmd_args_err_msg();

#define GAME_OF_LIFE_CLIENT_UTILS_H
#endif