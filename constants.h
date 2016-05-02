/*add_volatile
   constantes.h

   @author Remy Betus <remy.betus@gmail.com>
 */
#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
    #define BLOCK_SIZE          25
    #define HORIZONTAL_BLOCK_NB 20
    #define VERTICAL_BLOCK_NB   30
    #define GAME_BORDER_WIDTH 2
    #define EXTRA_BLOCKS      2 // Extra blocks on left/right to virtually keep MATRIX_FILL blocks
    #define VIRTUAL_HORIZONTAL_BLOCK_NB HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS*2
    #define VIRTUAL_VERTICAL_BLOCK_NB   VERTICAL_BLOCK_NB + EXTRA_BLOCKS*2
    #define GAME_INFOS_WIDTH  200
    #define GAME_AREA_WIDTH   BLOCK_SIZE * HORIZONTAL_BLOCK_NB + GAME_BORDER_WIDTH * 2
    #define GAME_AREA_HEIGHT  BLOCK_SIZE * VERTICAL_BLOCK_NB + GAME_BORDER_WIDTH * 2
    #define WINDOW_WIDTH      GAME_AREA_WIDTH + MATRIX_FILL*2 + GAME_INFOS_WIDTH
    #define WINDOW_HEIGHT     GAME_AREA_HEIGHT

typedef enum {EMPTY = 0, BLOCK = 1, CURRENT = 2, MATRIX_FILL = 3} block;
typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t alpha;
} pixel;
#endif
