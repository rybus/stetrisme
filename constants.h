/*add_volatile
   constantes.h

   @author Remy Betus <remy.betus@gmail.com>
 */
#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
    #define BLOCK_SIZE      25
    #define WIDTH_BLOCK_NB   20
    #define HEIGHT_BLOCK_NB  30
    #define GAME_BORDER_WIDTH 2
    #define EXTRA_MATRIX_FILL 2 // Extra bloc on left/right to virtually keep MATRIX_FILL
    #define GAME_INFOS_WIDTH 200
    #define GAME_AREA_WIDTH BLOCK_SIZE * WIDTH_BLOCK_NB + GAME_BORDER_WIDTH * 2
    #define GAME_AREA_HEIGHT BLOCK_SIZE * HEIGHT_BLOCK_NB + GAME_BORDER_WIDTH * 2
    #define WINDOW_WIDTH     GAME_AREA_WIDTH + MATRIX_FILL*2 + GAME_INFOS_WIDTH
    #define WINDOW_HEIGHT    GAME_AREA_HEIGHT

typedef enum {EMPTY = 0, BLOCK = 1, CURRENT = 2, MATRIX_FILL = 3} block;
typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t alpha;
} pixel;
#endif
