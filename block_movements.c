#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"
#include "block_creations.h"

int isDownMovable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	int x, y;

	for(x = 0; x < HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS; x++) {
		for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (current_grid[x][y] == CURRENT) {
				if (y == VERTICAL_BLOCK_NB - 1 || grid[x][y + 1] == BLOCK) {
					return 0;
				}
			}
		}
	}

	return 1;
}

int moveDown(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score)
{
	if (isDownMovable(current_grid, grid)) {
		for(int x = 0; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS * 2; x++) {
			for (int y = VERTICAL_BLOCK_NB - 1; y >= 0; y--) {
				if (current_grid[x][y] != EMPTY) {
					current_grid[x][y + 1] = current_grid[x][y];
					current_grid[x][y] = EMPTY;
				}
			}
		}

		return 1;
	} else
		return next_tetromino(current_grid, grid, score);

}

int moveFullDown(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score)
{
	while (isDownMovable(current_grid, grid)) {
		for (int x = 0; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS * 2; x++) {
			for (int y = VERTICAL_BLOCK_NB - 1; y >= 0; y--) {
				if (current_grid[x][y] != EMPTY) {
					current_grid[x][y + 1] = current_grid[x][y];
					current_grid[x][y] = EMPTY;
				}
			}
		}
	}

	return next_tetromino(current_grid, grid, score);
}

int isLeftMovable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	for(int x = EXTRA_BLOCKS; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
		for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (current_grid[x][y] == CURRENT) {
				if (x == EXTRA_BLOCKS)
					return 0;
				else if (grid[x - 1][y] == BLOCK || grid[x - 1][y] == BORDER_BLOCK)
					return 0;
			}
		}
	}

	return 1;
}

void moveLeft(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	if (isLeftMovable(current_grid, grid)) {
		for (int x = 0; x < HORIZONTAL_BLOCK_NB + 2*EXTRA_BLOCKS; x++) {
			for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
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
	for(int x = EXTRA_BLOCKS - 1; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
		for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (x == (HORIZONTAL_BLOCK_NB  + EXTRA_BLOCKS - 1) && (current_grid[HORIZONTAL_BLOCK_NB  + EXTRA_BLOCKS - 1][y] == CURRENT)) {
				return 0;
			}
			if (current_grid[x][y] == CURRENT && (x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS - 1) && grid[x + 1][y] == BLOCK) {
				return 0;
			}
		}
	}

	return 1;
}

void moveRight(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB])
{
	if (isRightMovable(current_grid, grid)) {
		for(int x = HORIZONTAL_BLOCK_NB + 2*EXTRA_BLOCKS - 1; x >= 0; x--) {
			for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
				if (current_grid[x][y] != EMPTY) {
					current_grid[x + 1][y] = current_grid[x][y];
					current_grid[x][y] = EMPTY;
				}
			}
		}
	}
}
