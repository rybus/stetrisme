Tetromino_t get_next_tetromino(void);
int next_tetromino(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score);
int isLineFull(block grid[][VERTICAL_BLOCK_NB], int line_number);
void remove_full_lines(block grid[][VERTICAL_BLOCK_NB], int * score);
void shiftGrid(block grid[][VERTICAL_BLOCK_NB], int line_number);
