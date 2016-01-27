/*
constantes.h

@author Remy Betus <remy.betus@gmail.com>
*/

#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

    #define BLOCK_SIZE      23
    #define WIDTH_BLOCK_NB  12
    #define HEIGHT_BLOCK_NB 24
    #define WINDOW_WIDTH    BLOCK_SIZE  * WIDTH_BLOCK_NB
    #define WINDOW_HEIGHT   BLOCK_SIZE  * HEIGHT_BLOCK_NB

    enum {UP, DOWN, LEFT, RIGHT};
    enum {ANGLE_0, ANGLE_90, ANGLE_180, ANGLE_270};
    enum {EMPTY, BLOCK};

    int tetrimino_i[4][4][4] = {
    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}},
    {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}}};
#endif