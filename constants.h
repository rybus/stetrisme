/*add_volatile
constantes.h

@author Remy Betus <remy.betus@gmail.com>
*/
#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
    #define BLOCK_SIZE      23
    #define WIDTH_BLOCK_NB   19
    #define HEIGHT_BLOCK_NB  34
    #define WINDOW_WIDTH     640
    #define WINDOW_HEIGHT    800

    typedef enum {EMPTY = 0, BLOCK = 1, CURRENT = 2, MATRIX_FILL = 3} block;
    typedef struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t alpha;
    } pixel;
#endif
