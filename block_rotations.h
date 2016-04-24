void rotateClockWise(block grid[][HEIGHT_BLOCK_NB], block current_grid[][HEIGHT_BLOCK_NB]);
void rotateCounterClockWise(block grid[][HEIGHT_BLOCK_NB], block current_grid[][HEIGHT_BLOCK_NB]);

int isClockWiseRotatable(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB], int min_x,int max_x,int min_y,int max_y);
int isCounterClockwiseRotatable(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);

int rotateBlockClockWise(block current_grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);
int rotateBlockCounterClockWise(block grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);

void getMatrixDimensions(block grid[][HEIGHT_BLOCK_NB], int *min_x, int *max_x, int *min_y, int *max_y);
int transpose(block grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);
void reverseRows(block grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);
void reverseColumns(block grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);

void printMatrix(block **grid, int x, int y);
void printGrid(block grid[][HEIGHT_BLOCK_NB]);
