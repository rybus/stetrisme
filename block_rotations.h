void rotateClockwise(block grid[][HEIGHT_BLOCK_NB], block current_grid[][HEIGHT_BLOCK_NB]);
int isClockWiseRotatable(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB], int min_x,int max_x,int min_y,int max_y);
void rotateBlockClockWise(block current_grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);
void getMatrixDimensions(block grid[][HEIGHT_BLOCK_NB], int *min_x, int *max_x, int *min_y, int *max_y);
