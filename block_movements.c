#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"
#include "block_creations.h"

int isDownMovable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB])
{
	for (int x = 0; x < HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS; x++) {
		for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (current_grid[x][y] == CURRENT) {
				if (y == VERTICAL_BLOCK_NB - 1 || grid[x][y + 1] == BLOCK)
					return 0;
			}
		}
	}

	return 1;
}

int moveDown(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int * score, int * level, int * cleared_lines)
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
		return next_tetromino(current_grid, grid, score, level, cleared_lines);

}

int moveFullDown(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int * score, int * level, int * cleared_lines)
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

	return next_tetromino(current_grid, grid, score, level, cleared_lines);
}

int isLeftMovable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB])
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

void moveLeft(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB])
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


int isRightMovable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB])
{
	for(int x = EXTRA_BLOCKS - 1; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
		for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (x == (HORIZONTAL_BLOCK_NB  + EXTRA_BLOCKS - 1) && (current_grid[HORIZONTAL_BLOCK_NB  + EXTRA_BLOCKS - 1][y] == CURRENT))
				return 0;
			if (current_grid[x][y] == CURRENT && (x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS - 1) && grid[x + 1][y] == BLOCK)
				return 0;
		}
	}

	return 1;
}

void moveRight(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB])
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
