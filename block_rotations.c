#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "constants.h"
#include "block_rotations.h"

void rotateClockWise(block grid[][VERTICAL_BLOCK_NB], block current_grid[][VERTICAL_BLOCK_NB])
{
	int min_x = HORIZONTAL_BLOCK_NB, max_x = 0;
	int min_y = VERTICAL_BLOCK_NB, max_y = 0;

	getMatrixDimensions(current_grid, &min_x, &max_x, &min_y, &max_y);
	if (isClockWiseRotatable(current_grid, grid, min_x, max_x, min_y, max_y)) {
		rotateBlockClockWise(current_grid, min_x, max_x, min_y, max_y);
	}
}

int isClockWiseRotatable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	block fake_grid[HORIZONTAL_BLOCK_NB][VERTICAL_BLOCK_NB];

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			fake_grid[x][y] = grid[x][y];
		}
	}

	if (0 == rotateBlockClockWise(fake_grid, min_x, max_x, min_y, max_y)) {
		return 0;
	}

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			if(fake_grid[x][y] == CURRENT && grid[x][y] == BLOCK) {
				return 0;
			}
		}
	}

	return 1;
}

void rotateCounterClockWise(block grid[][VERTICAL_BLOCK_NB], block current_grid[][VERTICAL_BLOCK_NB])
{
	int min_x = HORIZONTAL_BLOCK_NB, max_x = 0;
	int min_y = VERTICAL_BLOCK_NB, max_y = 0;
	getMatrixDimensions(current_grid, &min_x, &max_x, &min_y, &max_y);

	if (isCounterClockwiseRotatable(current_grid, grid, min_x, max_x, min_y, max_y)) {
		rotateBlockCounterClockWise(current_grid, min_x, max_x, min_y, max_y);
	}
}

int isCounterClockwiseRotatable(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	block fake_grid[HORIZONTAL_BLOCK_NB][VERTICAL_BLOCK_NB];

	memcpy(fake_grid, current_grid, sizeof(fake_grid));

	rotateBlockCounterClockWise(fake_grid, min_x, max_x, min_y, max_y);
	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			if(fake_grid[x][y] == CURRENT && grid[x][y] == BLOCK) {
				return 0;
			}
		}
	}

	return 1;
}

int rotateBlockClockWise(block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	if (1 == transpose(grid, min_x, max_x, min_y, max_y)) {
		reverseColumns(grid, min_x, max_x, min_y, max_y);

		return 1;
	}
	return 0;
}

int rotateBlockCounterClockWise(block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	if (1 == transpose(grid, min_x, max_x, min_y, max_y)) {
		reverseRows(grid, min_x, max_x, min_y, max_y);

		return 1;
	}
	return 0;
}

int transpose(block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	int dimension = (max_x - min_x) + 1;

	if ((max_x + dimension)/2 > HORIZONTAL_BLOCK_NB) {
		printf("Max_x: %d, dimension: %d\n", max_x, dimension);
		return 0;
	}

	block **transposed;
	transposed = (block ** ) malloc (dimension * sizeof (block*));
	for (int i = 0; i < dimension; i++) {
		transposed[i] = (block *) malloc(dimension * sizeof(block));
	}

	for (int i = 0; i < dimension; ++i) {
		for (int j = 0; j < dimension; ++j) {
			transposed[i][j] = grid[min_x + i][min_y + j];
		}
	}

	for (int j = min_y; j <= max_y; j++) {
		for (int i = min_x; i <= max_x; i++) {
			grid[i][j] = transposed[j - min_y][i - min_x];
		}
	}

	return 1;
}



void printGrid(block grid[][VERTICAL_BLOCK_NB])
{
	for (int j = 0; j < VERTICAL_BLOCK_NB; j++) {
		for (int i = 0; i < HORIZONTAL_BLOCK_NB; i++) {


			printf("%d ", grid[i][j]);

		}
		printf("\n");
	}
	printf("\n");
}

void reverseRows(block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	block reversed_grid[HORIZONTAL_BLOCK_NB][VERTICAL_BLOCK_NB];

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			reversed_grid[x][y] = grid[x][max_y - y + min_y];
		}
	}

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			grid[x][y] = reversed_grid[x][y];
		}
	}
}

void reverseColumns(block grid[][VERTICAL_BLOCK_NB], int min_x, int max_x, int min_y, int max_y)
{
	block reversed_grid[HORIZONTAL_BLOCK_NB][VERTICAL_BLOCK_NB];

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			reversed_grid[x][y] = grid[max_x - x + min_x][y];
		}
	}

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			grid[x][y] = reversed_grid[x][y];
		}
	}
}

void getMatrixDimensions(block grid[][VERTICAL_BLOCK_NB], int *min_x, int *max_x, int *min_y, int *max_y)
{
	int x, y;

	for(x = 0; x < HORIZONTAL_BLOCK_NB; x++) {
		for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
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
