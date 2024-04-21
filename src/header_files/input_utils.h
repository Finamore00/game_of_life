#ifndef GAME_OF_LIFE_INPUT_UTILS_H

#define WRITE_FILE_ERR -1
#define FILE_ALREADY_EXISTS_ERR -2
#define FILE_CREATION_ERR -3
#define FILE_CREATION_SUCCESS 0
#define FILE_ACCESS_ERR -1
#define FILE_READ_ERR -2
#define FILE_READ_SUCCESS 0

int generate_input_file(const char *file_path);
int read_input_file(char *file_path, int grid[][GRID_WIDTH]);
void generate_random_grid(int (*grid)[GRID_WIDTH]);

#define GAME_OF_LIFE_INPUT_UTILS_H
#endif