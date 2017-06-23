#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <errno.h>
#include <libconfig.h>

#include "constants.h"
#include "draw_game.h"
#include "tetromino.h"

SDL_Surface *a_block, *b_block, *background;
TTF_Font *opensans_30_font, *opensans_20_font;
SDL_Color white_color  = {255, 255, 255};

int initialize_color_blocks(Config_t config)
{
    opensans_30_font = TTF_OpenFont("resources/opensans.ttf", 30);
    opensans_20_font = TTF_OpenFont("resources/opensans.ttf", 20);

    background = SDL_CreateRGBSurface(0, BLOCK_SIZE, BLOCK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 0, 0, 0));

    a_block = SDL_CreateRGBSurface(0, BLOCK_SIZE, BLOCK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(a_block,
      NULL,
      SDL_MapRGB(
        a_block->format,
        config.left_eye_color.r,
        config.left_eye_color.g,
        config.left_eye_color.b
      )
    );

    b_block = SDL_CreateRGBSurface(0, BLOCK_SIZE, BLOCK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(b_block,
      NULL,
      SDL_MapRGB(
        b_block->format,
        config.right_eye_color.r,
        config.right_eye_color.g,
        config.right_eye_color.b
      )
    );
}

void draw_game(SDL_Surface *screen, Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino, int next_tetromino_type, Config_t config, int score, int level)
{
  SDL_Rect position;
  char score_label_text[6]          = "score";
  char maximum_score_label_text[11] = "max. score";
  char current_level_label_text[6]  = "level";

  erase_surface(screen);
  draw_game_borders(screen);

  position.x = GAME_AREA_WIDTH + 10;
  position.y = 70;
  print_positioned_game_information(screen, score_label_text, score, &position);

  position.y += 80;
  print_positioned_game_information(screen, maximum_score_label_text, config.high_score, &position);
  position.y += 80;
  print_positioned_game_information(screen, current_level_label_text, level, &position);

  draw_tetrominos(screen, grid, tetromino);
  draw_next_tetromino(screen, next_tetromino_type);

  SDL_Flip(screen);
}

void draw_tetrominos(SDL_Surface *screen, Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
  SDL_Rect position;
  for (int x = 0; x < HORIZONTAL_BLOCK_NB; x++) {
    for (int y = 2; y < VERTICAL_BLOCK_NB; y++) {
      position.x = x * BLOCK_SIZE + GAME_BORDER_WIDTH;
      position.y = y * BLOCK_SIZE + GAME_BORDER_WIDTH;

      if (grid[x][y] == FIXED_BLOCK)
        SDL_BlitSurface(a_block, NULL, screen, &position);
      else
        SDL_BlitSurface(background, NULL, screen, &position);
    }
  }

  for (int x = tetromino.pos.x; x < tetromino.pos.x + TETROMINO_LENGTH; x++) {
     for (int y = tetromino.pos.y; y < tetromino.pos.y + TETROMINO_LENGTH; y++) {
      position.x = x * BLOCK_SIZE + GAME_BORDER_WIDTH;
      position.y = (y - 2) * BLOCK_SIZE + GAME_BORDER_WIDTH;

      if (tetromino.block[x - tetromino.pos.x][y - tetromino.pos.y] == CURRENT_BLOCK)
        SDL_BlitSurface(b_block, NULL, screen, &position);
    }
  }
}

void draw_next_tetromino(SDL_Surface *screen, int next_tetromino_type)
{
    Tetromino_t nextTromino = get_tetromino(next_tetromino_type);
    char next_tetromino_text[5]  = "next";
    SDL_Surface *next_tetromino_text_surface;
    SDL_Rect position;

    position.y = 410;
    position.x = GAME_AREA_WIDTH + 10;
    next_tetromino_text_surface = TTF_RenderText_Blended(opensans_30_font, next_tetromino_text, white_color);
    SDL_BlitSurface(next_tetromino_text_surface, NULL, screen, &position);
    position.y += 50;

    for (int y = 0; y < 4; y++) {
      position.x = GAME_AREA_WIDTH + 10;
      for (int x = 0; x < 4; x++) {
        if (nextTromino.block[x][y] == CURRENT_BLOCK)
            SDL_BlitSurface(a_block, NULL, screen, &position);
        position.x += BLOCK_SIZE;
      }
      position.y += BLOCK_SIZE;
    }

    SDL_FreeSurface(next_tetromino_text_surface);
}

void draw_game_borders(SDL_Surface *screen)
{
  Pixel_t white_pixel;
  white_pixel.r = white_pixel.g = white_pixel.b = (Uint8) 0xff;
  white_pixel.alpha = (Uint8) 128;

  SDL_LockSurface(screen);

  for (int y = 0; y < WINDOW_HEIGHT; y++) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
      // bottom border
      if (y > WINDOW_HEIGHT - GAME_BORDER_WIDTH*2 && x < GAME_AREA_WIDTH)
        put_pixel(screen, x, y, &white_pixel);

      // left and right borders
      if (x < GAME_BORDER_WIDTH) {
        put_pixel(screen, x, y, &white_pixel);
        put_pixel(screen, GAME_AREA_WIDTH - GAME_BORDER_WIDTH + x, y, &white_pixel);
      }
    }
  }

  SDL_UnlockSurface(screen);
}

/**
* Draws a signel Pixel_t on the screen at the (x, y) position.
*/
void put_pixel(SDL_Surface* screen, int x, int y, Pixel_t* p)
{
  Uint32* p_screen = (Uint32*) screen->pixels;
  p_screen += y*screen->w+x;
  *p_screen = SDL_MapRGBA(screen->format, p->r, p->g, p->b, p->alpha);
}

/**
* Displays integer informations such as score, max. score or level.
*
* @param SDL_Surface surface
* @param char *label the label of the information
* @param int number the information itself
*/
void print_positioned_game_information(SDL_Surface *screen, char *label_text, int number, SDL_Rect *position)
{
  char number_text[10];
  SDL_Surface *label_surface, *number_surface;

  sprintf(number_text, "%d", number);
  label_surface = TTF_RenderText_Blended(opensans_30_font, label_text, white_color);
  SDL_BlitSurface(label_surface, NULL, screen, position);

  position->y += 40;
  number_surface = TTF_RenderText_Blended(opensans_20_font, number_text, white_color);
  SDL_BlitSurface(number_surface, NULL, screen, position);

  SDL_FreeSurface(number_surface);
  SDL_FreeSurface(label_surface);
}

/*
* Erases the surface with black
*
* @param SDL_Surface the surface to erase
*/
void erase_surface(SDL_Surface *surface)
{
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
}
