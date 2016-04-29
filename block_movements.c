#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"
#include "block_creations.h"

int isDownMovable(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB])
{
    int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
            if (current_grid[x][y] == CURRENT) {
                if (y == HEIGHT_BLOCK_NB - 1) {
                    return 0;
                } else if (grid[x][y + 1] == BLOCK) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

int moveDown(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB], int * score)
{
    int x, y;
    if (isDownMovable(current_grid, grid)) {
        for(x = 0; x < WIDTH_BLOCK_NB; x++) {
            for (y = HEIGHT_BLOCK_NB - 1; y >= 0; y--)
            {
                if (current_grid[x][y] != EMPTY) {
                    current_grid[x][y + 1] = current_grid[x][y];
                    current_grid[x][y] = EMPTY;
                }
            }
        }

        return 1;
    } else {
        return nextTetrino(current_grid, grid, score);
    }
}

int isLeftMovable(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB])
{
    int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
            if (x == 0 && current_grid[0][y] == CURRENT) {
                return 0;
            } else if (x != 0 && current_grid[x][y] == CURRENT && grid[x - 1][y] == BLOCK) {
                return 0;
            }
        }
    }

    return 1;
}

void moveLeft(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB])
{
    int x, y;
    if (isLeftMovable(current_grid, grid)) {
        for(x = 0; x < WIDTH_BLOCK_NB; x++) {
            for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
                if (current_grid[x][y] != EMPTY) {
                    current_grid[x - 1][y] = current_grid[x][y];
                    current_grid[x][y] = EMPTY;
                }
            }
        }
    }
}


int isRightMovable(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB])
{
   int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
            if (x == (WIDTH_BLOCK_NB - 1) && (current_grid[WIDTH_BLOCK_NB - 1][y] == CURRENT)) {
                return 0;
            } else if (current_grid[x][y] == CURRENT && (x < WIDTH_BLOCK_NB - 2) && grid[x + 1][y] == BLOCK) {
                return 0;
            }
        }
    }

    return 1;
}

void moveRight(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB])
{
    int x, y;
    if (isRightMovable(current_grid, grid)) {
        for(x = WIDTH_BLOCK_NB; x >= 0 ; x--) {
            for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
                if (current_grid[x][y] != EMPTY) {
                    current_grid[x + 1][y] = current_grid[x][y];
                    current_grid[x][y] = EMPTY;
                }
            }
        }
    }
}
