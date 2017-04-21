#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "constants.h"
#include "block_rotations.h"

void rotateClockWise(Block grid[][VERTICAL_BLOCK_NB], Block current_grid[][VERTICAL_BLOCK_NB])
{
	int min_x = HORIZONTAL_BLOCK_NB, max_x = 0;
	int min_y = VERTICAL_BLOCK_NB, max_y = 0;

	getMatrixDimensions(current_grid, &min_x, &max_x, &min_y, &max_y);
	if (isClockWiseRotatable(current_grid, grid, min_x, max_x, min_y, max_y))
		rotateBlockClockWise(current_grid, min_x, max_x, min_y, max_y);
}

int isClockWiseRotatable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	Block fake_grid[HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS][VERTICAL_BLOCK_NB];
    int x, y;

	if (isSquare(current_grid))
		return 0;

	for (y = min_y; y <= max_y; y++) {
		for (x = min_x; x <= max_x; x++)
			fake_grid[x][y] = current_grid[x][y];
	}

	if (0 == rotateBlockClockWise(fake_grid, min_x, max_x, min_y, max_y)) {
		return 0;
	}

	for (y = min_y; y <= max_y; y++) {
		for (x = min_x; x <= max_x; x++) {
			if(fake_grid[x][y] == CURRENT) {
				if (x < EXTRA_BLOCKS || x > HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS)
					return 0;
				if (grid[x][y] == BLOCK || grid[x][y] == BORDER_BLOCK)
					return 0;
			}
		}
	}

	return 1;
}

void rotateCounterClockWise(Block grid[][VERTICAL_BLOCK_NB], Block current_grid[][VERTICAL_BLOCK_NB])
{
	int min_x = HORIZONTAL_BLOCK_NB + (2 * EXTRA_BLOCKS), max_x = 0;
	int min_y = VERTICAL_BLOCK_NB, max_y = 0;

	getMatrixDimensions(current_grid, &min_x, &max_x, &min_y, &max_y);

	if (isCounterClockwiseRotatable(current_grid, grid, min_x, max_x, min_y, max_y))
		rotateBlockCounterClockWise(current_grid, min_x, max_x, min_y, max_y);
}

int isCounterClockwiseRotatable(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	Block fake_grid[HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS][VERTICAL_BLOCK_NB];

	if (isSquare(current_grid))
		return 0;
	memcpy(fake_grid, current_grid, sizeof(fake_grid));

	rotateBlockCounterClockWise(fake_grid, min_x, max_x, min_y, max_y);
	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
				if(fake_grid[x][y] == CURRENT) {
					if (x < EXTRA_BLOCKS || x > HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS)
						return 0;
					if (grid[x][y] == BLOCK || grid[x][y] == BORDER_BLOCK)
						return 0;
				}
		}
	}

	return 1;
}

int isSquare(Block current_grid[][VERTICAL_BLOCK_NB])
{
	int min_x = HORIZONTAL_BLOCK_NB, max_x = 0;
	int min_y = VERTICAL_BLOCK_NB, max_y = 0;

	for (int x = 0; x < HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS; x++) {
		for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (current_grid[x][y] == CURRENT) {
				if (x < min_x)
					min_x = x;
				if (x > max_x)
					max_x = x;
				if (y < min_y)
					min_y = y;
				if (y > max_y)
					max_y = y;
			}
		}
	}
	if (max_x - min_x == max_y - min_y)
		return 1;
	else
		return 0;
}

int rotateBlockClockWise(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	if (transpose(grid, min_x, max_x, min_y, max_y)) {
		reverseColumns(grid, min_x, max_x, min_y, max_y);

		return 1;
	}
	return 0;
}

int rotateBlockCounterClockWise(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	if (transpose(grid, min_x, max_x, min_y, max_y)) {
		reverseRows(grid, min_x, max_x, min_y, max_y);

		return 1;
	}
	return 0;
}

int transpose(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	int dimension = (max_x - min_x) + 1;
    int i, j;

	if ((max_x + dimension)/2 > HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS)
		return 0;

	Block **transposed;
	transposed = (Block ** ) malloc (dimension * sizeof (Block*));
	for (i = 0; i < dimension; i++)
		transposed[i] = (Block *) malloc(dimension * sizeof(Block));

	for (i = 0; i < dimension; ++i) {
		for (j = 0; j < dimension; ++j)
			transposed[i][j] = grid[min_x + i][min_y + j];
	}

	for (j = min_y; j <= max_y; j++) {
		for (i = min_x; i <= max_x; i++)
			grid[i][j] = transposed[j - min_y][i - min_x];
	}

	return 1;
}

void reverseRows(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	Block reversed_grid[HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS][VERTICAL_BLOCK_NB];

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++)
			reversed_grid[x][y] = grid[x][max_y - y + min_y];
	}

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++)
			grid[x][y] = reversed_grid[x][y];
	}
}

void reverseColumns(Block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	Block reversed_grid[HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS][VERTICAL_BLOCK_NB];

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++)
			reversed_grid[x][y] = grid[max_x - x + min_x][y];
	}

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++)
			grid[x][y] = reversed_grid[x][y];
	}
}

void getMatrixDimensions(Block grid[][VERTICAL_BLOCK_NB], int *min_x, int *max_x, int *min_y, int *max_y)
{
	for(int x = 0; x < HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS; x++) {
		for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (grid[x][y] == CURRENT || grid[x][y] == MATRIX_FILL) {
				if (x < *min_x)
					*min_x = x;
				if (x > *max_x)
					*max_x = x;
				if (y < *min_y)
					*min_y = y;
				if (y > *max_y)
					*max_y = y;
			}
		}
	}
}
