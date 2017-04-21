void rotateClockWise(Block grid[][VERTICAL_BLOCK_NB], Block current_grid[][VERTICAL_BLOCK_NB]);
void rotateCounterClockWise(Block grid[][VERTICAL_BLOCK_NB], Block current_grid[][VERTICAL_BLOCK_NB]);

int isClockWiseRotatable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int min_x,int max_x,int min_y,int max_y);
int isCounterClockwiseRotatable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);

int rotateBlockClockWise(Block current_grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);
int rotateBlockCounterClockWise(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);

void getMatrixDimensions(Block grid[][VERTICAL_BLOCK_NB], int *min_x, int *max_x, int *min_y, int *max_y);
int transpose(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);
void reverseRows(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);
void reverseColumns(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y);

void printMatrix(Block **grid, int x, int y);
int isSquare(Block current_grid[][VERTICAL_BLOCK_NB]);
