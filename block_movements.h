int isDownMovable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB]);
int isLeftMovable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB]);
int isRightMovable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB]);
void moveLeft();
void moveRight(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB]);
int moveDown(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int *score, int * level, int * clear_lines, int *);
int moveFullDown(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int * score, int * level, int * clear_lines, int *);
