#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "constants.h"
#include "block_creations.h"

int line_factors[4] = {
	ONE_LINE_FACTOR,
	TWO_LINES_FACTOR,
	THREE_LINES_FACTOR,
	FOUR_LINES_FACTOR
};

Tetromino_t get_next_tetromino(void)
{
	Tetromino_t tetromino = { .block = {{2, 2, 2, 2},
		 {1, 1, 1, 1},
		 {2, 2, 2, 2},
		 {2, 2, 2, 2}}
	 };

	Tetromino_t tetrominos[7] = {
		{ .block =
		{{2, 2, 2, 2},
		 {1, 1, 1, 1},
		 {2, 2, 2, 2},
		 {2, 2, 2, 2}}},

		{ .block =
		{{2, 1, 1, 0},
		 {2, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}}},

		{ .block =
		{{2, 1, 2, 0},
		 {1, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}}},

		{ .block =
		{{2, 2, 1, 0},
		 {1, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}}},

		{ .block =
		{{1, 2, 2, 0},
		 {1, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}}},

		{ .block =
		{{1, 1, 2, 0},
		 {2, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}}},

		{ .block =
		{{2, 1, 1, 0},
		 {1, 1, 2, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}}}
	};

	srand(time(NULL));
	int tetromino_number = rand() % 7;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			tetromino.block[i][j] = tetrominos[tetromino_number].block[i][j];
	}

	return tetromino;
}

int next_tetromino(Block current_grid[][VERTICAL_BLOCK_NB], Block grid[][VERTICAL_BLOCK_NB], int * score, int * level)
{
	Tetromino_t tetromino;

	for(int x = 0; x < HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS; x++) {
		for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (current_grid[x][y] == CURRENT)
				grid[x][y] = BLOCK;
			current_grid[x][y] = EMPTY;
		}
	}

	remove_full_lines(grid, score, level);
	tetromino = get_next_tetromino();

	for(int x = (HORIZONTAL_BLOCK_NB/2); x < (HORIZONTAL_BLOCK_NB/2)+4; x++) {
		for (int y = 0; y < 4; y++) {
			if (tetromino.block[x - (HORIZONTAL_BLOCK_NB/2)][y] == 1 && grid[x][y] == BLOCK)
				return 0;

			if (tetromino.block[x - (HORIZONTAL_BLOCK_NB/2)][y] == 1)
				current_grid[x][y] = CURRENT;

			if (tetromino.block[x - (HORIZONTAL_BLOCK_NB/2)][y] == 2)
				current_grid[x][y] = MATRIX_FILL;
		}
	}

	return 1;
}

void remove_full_lines(Block grid[][VERTICAL_BLOCK_NB], int * score, int * level)
{
	int factor = 0;
	for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
		if (isLineFull(grid, y)) {
			shiftGrid(grid, y);
			factor++;
		}
	}

	if (factor > 0)
		*score = *score + line_factors[factor]*(1 + *level);
}

int isLineFull(Block grid[][VERTICAL_BLOCK_NB], int line_number)
{
	for(int x = EXTRA_BLOCKS; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
		if (grid[x][line_number] == EMPTY)
			return 0;
	}

	return 1;
}

void shiftGrid(Block grid[][VERTICAL_BLOCK_NB], int line_number)
{
	for (int y = line_number; y >= 0; y--) {
		for(int x = EXTRA_BLOCKS; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
			if (y == 0)
				grid[x][0] = EMPTY;
			else
				grid[x][y] = grid[x][y - 1];
		}
	}
}
