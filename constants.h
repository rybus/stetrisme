#include <SDL/SDL.h>

#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
    #define COLOR_SWITCH_NB_FALLEN_BLOCK 10
    #define BLOCK_SIZE          30
    #define HORIZONTAL_BLOCK_NB 10
    #define VERTICAL_BLOCK_NB   22
    #define LINES_PER_LEVEL     10
    #define DEFAULT_SPEED_MS    500
    #define ONE_LINE_FACTOR     40
    #define TWO_LINES_FACTOR    100
    #define THREE_LINES_FACTOR  300
    #define FOUR_LINES_FACTOR 1200
    #define GAME_BORDER_WIDTH 2
    #define GAME_INFOS_WIDTH  200
    #define GAME_AREA_WIDTH   BLOCK_SIZE * HORIZONTAL_BLOCK_NB + GAME_BORDER_WIDTH * 2
    #define GAME_AREA_HEIGHT  BLOCK_SIZE * VERTICAL_BLOCK_NB + GAME_BORDER_WIDTH * 2
    #define WINDOW_WIDTH      GAME_AREA_WIDTH + GAME_BORDER_WIDTH*2 + GAME_INFOS_WIDTH
    #define WINDOW_HEIGHT     GAME_AREA_HEIGHT
    #define PLAY_OPTION       0
    #define CONFIGURE_OPTION  1
    #define TETROMINO_LENGTH  4
    #define EXCLUDE_STUFFING  1
    #define INCLUDE_STUFFING  0

typedef enum block {
  EMPTY = 0,
  FIXED_BLOCK = 1,
  CURRENT_BLOCK = 2,
  STUFFING_BLOCK = 3
} Block;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t alpha;
} Pixel_t;

typedef struct {
    Block block[4][4];
    SDL_Rect pos;
} Tetromino_t;

typedef struct {
    int r;
    int g;
    int b;
} Color_t;

typedef struct {
  int min_x;
  int max_x;
  int min_y;
  int max_y;
} Dimension_t;

typedef struct {
   int high_score;
   Color_t left_eye_color;
   Color_t right_eye_color;
} Config_t;

#endif
