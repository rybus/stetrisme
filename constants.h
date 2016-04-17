/*
constantes.h

@author Remy Betus <remy.betus@gmail.com>
*/

#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
    #define BLOCK_SIZE      23
    #define WIDTH_BLOCK_NB  17
    #define HEIGHT_BLOCK_NB 24
    #define WINDOW_WIDTH    BLOCK_SIZE  * WIDTH_BLOCK_NB
    #define WINDOW_HEIGHT   BLOCK_SIZE  * HEIGHT_BLOCK_NB

    // enum {ANGLE_0, ANGLE_90, ANGLE_180, ANGLE_270};
    typedef enum {EMPTY = 0, BLOCK = 1, CURRENT = 2} block_types;
#endif
