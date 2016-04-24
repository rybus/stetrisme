void get_next_tetrimino(int tetrino[][4]);
int nextTetrino(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB], int * score);
int isLineFull(block grid[][HEIGHT_BLOCK_NB], int line_number);
void removeFullLines(block grid[][HEIGHT_BLOCK_NB], int * score);
void shiftGrid(block grid[][HEIGHT_BLOCK_NB], int line_number);
