#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void get_next_tetrimino(int tetrino[][4])
{
    int tetrimino[7][4][4] = {
                                {{1, 1, 1, 1},
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0}},

                                {{0, 0, 0, 0},
                                 {0, 1, 1, 0},
                                 {0, 1, 1, 0},
                                 {0, 0, 0, 0}},

                                {{0, 0, 0, 0},
                                 {0, 1, 1, 1},
                                 {0, 0, 1, 0},
                                 {0, 0, 0, 0}},

                                {{0, 0, 0, 0},
                                 {0, 1, 1, 1},
                                 {0, 1, 0, 0},
                                 {0, 0, 0, 0}},

                                {{0, 0, 0, 0},
                                 {0, 1, 1, 1},
                                 {0, 0, 0, 1},
                                 {0, 0, 0, 0}},

                                {{0, 0, 0, 0},
                                 {0, 1, 1, 0},
                                 {0, 0, 1, 1},
                                 {0, 0, 0, 0}},

                                {{0, 0, 0, 0},
                                 {0, 0, 1, 1},
                                 {0, 1, 1, 0},
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
