void initialize_game(Block grid[][VERTICAL_BLOCK_NB]);
Tetromino_t next_tetromino(Block grid[][VERTICAL_BLOCK_NB], int *score, int *next_tetromino_type);
int place_current_tetromino(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino);
int block_current_tetromino(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino);
int can_be_placed(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino);
int can_move_down(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino);
int can_move_left(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino);
int can_move_right(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino);
void remove_full_lines(Block grid[][VERTICAL_BLOCK_NB], int * score);
int is_line_full(Block grid[][VERTICAL_BLOCK_NB], int line_number);
void remove_line(Block grid[][VERTICAL_BLOCK_NB], int line_number);
int can_rotate_clockwise(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino);
int can_rotate_counter_clockwise(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino);
int is_grid_full(Block grid[][VERTICAL_BLOCK_NB]);