int isDownMovable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB]);
int isLeftMovable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB]);
int isRightMovable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB]);
int moveDown(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int *score);
void moveLeft();
void moveRight(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB]);
int moveFullDown(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score);
