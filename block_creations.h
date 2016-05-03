void get_next_tetrimino(int tetrino[][4]);
int nextTetrino(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score);
int isLineFull(block grid[][VERTICAL_BLOCK_NB], int line_number);
void removeFullLines(block grid[][VERTICAL_BLOCK_NB], int * score);
void shiftGrid(block grid[][VERTICAL_BLOCK_NB], int line_number);
