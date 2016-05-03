#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"
#include "block_creations.h"

int isDownMovable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	int x, y;

	for(x = 0; x < HORIZONTAL_BLOCK_NB; x++) {
		for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (current_grid[x][y] == CURRENT) {
				if (y == VERTICAL_BLOCK_NB - 1) {
					return 0;
				} else if (grid[x][y + 1] == BLOCK) {
					return 0;
				}
			}
		}
	}

	return 1;
}

int moveDown(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score)
{
	int x, y;
	if (isDownMovable(current_grid, grid)) {
		for(x = 0; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS * 2; x++) {
			for (y = VERTICAL_BLOCK_NB - 1; y >= 0; y--)
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

int moveFullDown(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score)
{
	int x, y;
	while (isDownMovable(current_grid, grid)) {
		for(x = 0; x < HORIZONTAL_BLOCK_NB; x++) {
			for (y = VERTICAL_BLOCK_NB - 1; y >= 0; y--)
			{
				if (current_grid[x][y] != EMPTY) {
					current_grid[x][y + 1] = current_grid[x][y];
					current_grid[x][y] = EMPTY;
				}
			}
		}
	}

	return nextTetrino(current_grid, grid, score);
}

int isLeftMovable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	int x, y;

	for(x = EXTRA_BLOCKS; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
		for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (current_grid[x][y] == CURRENT) {
				if (x == EXTRA_BLOCKS) {
					return 0;
        } else if (grid[x - 1][y] == BLOCK || grid[x - 1][y] == BORDER_BLOCK) {
					return 0;
				}
			}
		}
	}

	return 1;
}

void moveLeft(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	int x, y;
	if (isLeftMovable(current_grid, grid)) {
		for(x = 0; x < HORIZONTAL_BLOCK_NB + 2*EXTRA_BLOCKS; x++) {
			for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
				if (current_grid[x][y] != EMPTY) {
					current_grid[x - 1][y] = current_grid[x][y];
					current_grid[x][y] = EMPTY;
				}
			}
		}
	}
}


int isRightMovable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	int x, y;

	for(x = EXTRA_BLOCKS; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS	; x++) {
		for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (x == (HORIZONTAL_BLOCK_NB  + EXTRA_BLOCKS - 1) && (current_grid[HORIZONTAL_BLOCK_NB  + EXTRA_BLOCKS - 1][y] == CURRENT)) {
				return 0;
			} else if (current_grid[x][y] == CURRENT && (x < HORIZONTAL_BLOCK_NB - 2) && grid[x + 1][y] == BLOCK) {
				return 0;
			}
		}
	}

	return 1;
}

void moveRight(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	int x, y;
	if (isRightMovable(current_grid, grid)) {
		for(x = HORIZONTAL_BLOCK_NB + 2*EXTRA_BLOCKS; x >= 0; x--) {
			for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
				if (current_grid[x][y] != EMPTY) {
					current_grid[x + 1][y] = current_grid[x][y];
					current_grid[x][y] = EMPTY;
				}
			}
		}
	}
}
