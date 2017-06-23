#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"
#include "matrix.h"

void transpose_array(Block tetromino[][TETROMINO_LENGTH])
{
    Dimension_t dimensions = get_matrix_dimensions(tetromino, INCLUDE_STUFFING);
	int dimension = (dimensions.max_x - dimensions.min_x) + 1;

	Block **transposed;
	transposed = (Block ** ) malloc (dimension * sizeof (Block*));

	for (int i = 0; i < dimension; i++)
		transposed[i] = (Block *) malloc(dimension * sizeof(Block));

	for (int i = 0; i < dimension; ++i) {
		for (int j = 0; j < dimension; ++j)
			transposed[i][j] = tetromino[dimensions.min_x + i][dimensions.min_y + j];
	}

	for (int j = dimensions.min_y; j <= dimensions.max_y; j++) {
		for (int i = dimensions.min_x; i <= dimensions.max_x; i++)
			tetromino[i][j] = transposed[j - dimensions.min_y][i - dimensions.min_x];
	}
}

void reverse_rows(Block tetromino[][TETROMINO_LENGTH])
{
    Block reversed_tetromino[4][4];
    Dimension_t dimensions = get_matrix_dimensions(tetromino, INCLUDE_STUFFING);

	for (int y = dimensions.min_y; y <= dimensions.max_y; y++) {
		for (int x = dimensions.min_x; x <= dimensions.max_x; x++)
			reversed_tetromino[x][y] = tetromino[x][dimensions.max_y - y + dimensions.min_y];
	}

	for (int y = dimensions.min_y; y <= dimensions.max_y; y++) {
		for (int x = dimensions.min_x; x <= dimensions.max_x; x++)
			tetromino[x][y] = reversed_tetromino[x][y];
	}
}

void reverse_columns(Block tetromino[][TETROMINO_LENGTH])
{
    Block reversed_tetromino[4][4];
    Dimension_t dimensions = get_matrix_dimensions(tetromino, INCLUDE_STUFFING);

	for (int y = dimensions.min_y; y <= dimensions.max_y; y++) {
		for (int x = dimensions.min_x; x <= dimensions.max_x; x++)
			reversed_tetromino[x][y] = tetromino[dimensions.max_x - x + dimensions.min_x][y];
	}

	for (int y = dimensions.min_y; y <= dimensions.max_y; y++) {
		for (int x = dimensions.min_x; x <= dimensions.max_x; x++)
			tetromino[x][y] = reversed_tetromino[x][y];
	}
}

Dimension_t get_matrix_dimensions(Block grid[][TETROMINO_LENGTH], int stuffing)
{
    Dimension_t dimension = {TETROMINO_LENGTH, 0, TETROMINO_LENGTH, 0};

	for (int x = 0; x < TETROMINO_LENGTH; x++) {
		for (int y = 0; y < TETROMINO_LENGTH; y++) {
			if (grid[x][y] == CURRENT_BLOCK
                || (stuffing == INCLUDE_STUFFING && grid[x][y] == STUFFING_BLOCK)
            ) {
				if (x < dimension.min_x)
					dimension.min_x = x;
				if (x > dimension.max_x)
					dimension.max_x = x;
				if (y < dimension.min_y)
					dimension.min_y = y;
				if (y > dimension.max_y)
				   dimension.max_y = y;
			}
		}
	}

    return dimension;
}
