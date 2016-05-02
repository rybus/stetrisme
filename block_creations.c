#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "constants.h"
#include "score.h"
#include "block_creations.h"

void get_next_tetrimino(int tetrino[][4])
{
	int tetrimino[7][4][4] = {
		{{2, 2, 2, 2},
		 {1, 1, 1, 1},
		 {2, 2, 2, 2},
		 {2, 2, 2, 2}},

		{{2, 1, 1, 0},
		 {2, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}},

		{{2, 1, 2, 0},
		 {1, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}},

		{{2, 2, 1, 0},
		 {1, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}},

		{{1, 2, 2, 0},
		 {1, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}},

		{{1, 1, 2, 0},
		 {2, 1, 1, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}},

		{{2, 1, 1, 0},
		 {1, 1, 2, 0},
		 {2, 2, 2, 0},
		 {0, 0, 0, 0}}
	};

	srand(time(NULL));
	int tetrimino_number = rand() % 7;
	tetrimino_number = 0;

	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tetrino[i][j] = tetrimino[tetrimino_number][i][j];
		}
	}
}

int nextTetrino(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score)
{
	int tetrino[4][4];
	int x, y;
	for(x = 0; x < HORIZONTAL_BLOCK_NB; x++) {
		for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
			if (current_grid[x][y] == CURRENT) {
				grid[x][y] = BLOCK;
			}
			current_grid[x][y] = EMPTY;
		}
	}

	removeFullLines(grid, score);

	get_next_tetrimino(tetrino);

	for(x = (HORIZONTAL_BLOCK_NB/2); x < (HORIZONTAL_BLOCK_NB/2)+4; x++) {
		for (y = 0; y < 4; y++) {
			if (tetrino[x - (HORIZONTAL_BLOCK_NB/2)][y] == 1 && grid[x][y] == BLOCK) {
				return 0;
			}
			if (tetrino[x - (HORIZONTAL_BLOCK_NB/2)][y] == 1) {
				current_grid[x][y] = CURRENT;
			}
			if (tetrino[x - (HORIZONTAL_BLOCK_NB/2)][y] == 2) {
				current_grid[x][y] = MATRIX_FILL;
			}
		}
	}

	return 1;
}

void removeFullLines(block grid[][VERTICAL_BLOCK_NB], int * score)
{
	int x, y;

	for (y = 0; y < VERTICAL_BLOCK_NB; y++) {
		if (isLineFull(grid, y)) {
			shiftGrid(grid, y);
			*score = *score + 10;
		}
	}

	update_high_score(*score);
}

int isLineFull(block grid[][VERTICAL_BLOCK_NB], int line_number)
{
	for(int x = EXTRA_BLOCKS; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
		if (grid[x][line_number] == EMPTY) {
			return 0;
		}
	}

	return 1;
}

void shiftGrid(block grid[][VERTICAL_BLOCK_NB], int line_number)
{
	for (int y = line_number; y >= 0; y--) {
		for(int x = EXTRA_BLOCKS; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
			if (y == 0) {
				grid[x][0] = EMPTY;
			} else {
				grid[x][y] = grid[x][y - 1];
			}
		}
	}
}
