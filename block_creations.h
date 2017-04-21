Tetromino_t get_tetromino(int);
int next_tetromino(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int * score, int * level, int * clear_lines, int *next_tetromino_type);
int isLineFull(Block grid[][VERTICAL_BLOCK_NB], int line_number);
void shiftGrid(Block grid[][VERTICAL_BLOCK_NB], int line_number);
void remove_full_lines(Block grid[][VERTICAL_BLOCK_NB], int * score, int * level, int * clear_lines);
