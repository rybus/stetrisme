/*add_volatile
   constantes.h

   @author Remy Betus <remy.betus@gmail.com>
 */
#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
    #define BLOCK_SIZE      25
    #define WIDTH_BLOCK_NB   19
    #define HEIGHT_BLOCK_NB  34
    #define GAME_BORDER_WIDTH 2
    #define WINDOW_WIDTH     BLOCK_SIZE * WIDTH_BLOCK_NB + GAME_BORDER_WIDTH * 2 + 200
    #define WINDOW_HEIGHT    BLOCK_SIZE * HEIGHT_BLOCK_NB + GAME_BORDER_WIDTH * 2

typedef enum {EMPTY = 0, BLOCK = 1, CURRENT = 2, MATRIX_FILL = 3} block;
typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t alpha;
} pixel;
#endif
