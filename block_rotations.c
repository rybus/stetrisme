#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "block_rotations.h"


void rotateClockwise(block grid[][HEIGHT_BLOCK_NB], block current_grid[][HEIGHT_BLOCK_NB])
{
    int min_x = WIDTH_BLOCK_NB, max_x = 0;
    int min_y = HEIGHT_BLOCK_NB, max_y = 0;
    getMatrixDimensions(current_grid, &min_x, &max_x, &min_y, &max_y);

    if (isClockWiseRotatable(current_grid, grid, min_x, max_x, min_y, max_y)) {
        rotateBlockClockWise(current_grid, min_x, max_x, min_y, max_y);
    }
}

int isClockWiseRotatable(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y) {
    block fake_grid[WIDTH_BLOCK_NB][HEIGHT_BLOCK_NB];
    memcpy(fake_grid, current_grid, sizeof(fake_grid));
    rotateBlockClockWise(fake_grid, min_x, max_x, min_y, max_y);
    for (int i = 0; i < WIDTH_BLOCK_NB; ++i) {
        for (int j = 0; j < HEIGHT_BLOCK_NB; ++j) {
            if(fake_grid[i][j] == CURRENT && grid[i][j] == BLOCK) {
                return 0;
            }
        }
    }

    return 1;
}

void rotateBlockClockWise(block current_grid[][HEIGHT_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
    block fake_grid[WIDTH_BLOCK_NB][HEIGHT_BLOCK_NB];
    for (int i = min_x; i <= max_x; ++i) {
        for (int j = min_y; j <= max_y; ++j) {
            fake_grid[i][j] = current_grid[max_x - j - 1][i];
        }
    }
    for (int i = 0; i < WIDTH_BLOCK_NB; ++i) {
        for (int j = 0; j < HEIGHT_BLOCK_NB; ++j) {
            current_grid[i][j] = fake_grid[i][j];
        }
    }
}

void getMatrixDimensions(block grid[][HEIGHT_BLOCK_NB], int *min_x, int *max_x, int *min_y, int *max_y)
{
    int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
           if (grid[x][y] == CURRENT || grid[x][y] == MATRIX_FILL) {
               if (x < *min_x) {
                    *min_x = x;
                }
                if (x > *max_x) {
                    *max_x = x;
                }
                if (y < *min_y) {
                    *min_y = y;
                }
                if (y > *max_y) {
                    *max_y = y;
                }
             }
        }
    }
}
