#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "constants.h"

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

    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tetrino[i][j] = tetrimino[tetrimino_number][i][j];
        }
    }
}

void nextTetrino(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB])
{
    int tetrino[4][4];
    int x, y;
    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
             if (current_grid[x][y] == CURRENT) {
                grid[x][y] = BLOCK;
             }
             current_grid[x][y] = EMPTY;
        }
    }

    get_next_tetrimino(tetrino);

    for(x = (WIDTH_BLOCK_NB/2); x < (WIDTH_BLOCK_NB/2)+4; x++) {
        for (y = 0; y < 4; y++) {
          if (tetrino[x - (WIDTH_BLOCK_NB/2)][y] == 1) {
                current_grid[x][y] = CURRENT;
          }
          if (tetrino[x - (WIDTH_BLOCK_NB/2)][y] == 2) {
                current_grid[x][y] = MATRIX_FILL;
          }
        }
    }

}
