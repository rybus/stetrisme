/*
   @author Remy Betus <remy.betus@gmail.com>
 */
#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
    #define BLOCK_SIZE          30
    #define HORIZONTAL_BLOCK_NB 10
    #define VERTICAL_BLOCK_NB   22
    #define ONE_LINE_FACTOR 40
    #define TWO_LINES_FACTOR 100
    #define THREE_LINES_FACTOR 300
    #define FOUR_LINES_FACTOR 1200
    #define GAME_BORDER_WIDTH 2
    #define EXTRA_BLOCKS      2 // Extra blocks on left/right to virtually keep MATRIX_FILL blocks
    #define GAME_INFOS_WIDTH  200
    #define GAME_AREA_WIDTH   BLOCK_SIZE * HORIZONTAL_BLOCK_NB + GAME_BORDER_WIDTH * 2
    #define GAME_AREA_HEIGHT  BLOCK_SIZE * VERTICAL_BLOCK_NB + GAME_BORDER_WIDTH * 2
    #define WINDOW_WIDTH      GAME_AREA_WIDTH + GAME_BORDER_WIDTH*2 + GAME_INFOS_WIDTH
    #define WINDOW_HEIGHT     GAME_AREA_HEIGHT - (2 * BLOCK_SIZE)
    #define PLAY_OPTION       0
    #define CONFIGURE_OPTION  1

typedef enum block {EMPTY = 0, BLOCK = 1, CURRENT = 2, MATRIX_FILL = 3, BORDER_BLOCK = 4} Block;
typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t alpha;
} Pixel_t;

typedef struct {
    int block[4][4];
} Tetromino_t;

typedef struct {
    int r;
    int g;
    int b;
} Color_t;

typedef struct {
   int high_score;
   Color_t left_eye_color;
   Color_t right_eye_color;
} Config_t;

#endif
