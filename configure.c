#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <errno.h>

#include "constants.h"
#include "config.h"
#include "configure.h"
#include "events.h"
#include "play.h"

Config_t config;
int currentPosition;

void configure(SDL_Surface *screen)
{
  Color_t *left_eye_color_ptr, *right_eye_color_ptr;
  int *selectors[6];

  Input in;

  memset(&in, 0, sizeof(in));
  config = load_config();

  left_eye_color_ptr = &config.left_eye_color;
  right_eye_color_ptr = &config.right_eye_color;

  erase_surface(screen);
  currentPosition = 0;

  selectors[0] = &(*left_eye_color_ptr).r;
  selectors[1] = &(*left_eye_color_ptr).g;
  selectors[2] = &(*left_eye_color_ptr).b;
  selectors[3] = &(*right_eye_color_ptr).r;
  selectors[4] = &(*right_eye_color_ptr).g;
  selectors[5] = &(*right_eye_color_ptr).b;

  while(!in.key[SDLK_ESCAPE])
  {
      UpdateEvents(&in);
      if (in.key[SDLK_LEFT]) {
          if (currentPosition > 0) {
              currentPosition--;
          }
          in.key[SDLK_LEFT] = 0;
      }
      if (in.key[SDLK_RIGHT]) {
          if (currentPosition < 6) {
              currentPosition++;
          }
          in.key[SDLK_RIGHT] = 0;
      }
      if (in.key[SDLK_UP]) {
          (*selectors[currentPosition])++;
          in.key[SDLK_UP] = 0;
      }
      if (in.key[SDLK_DOWN]) {
          (*selectors[currentPosition])--;
          in.key[SDLK_DOWN] = 0;
      }

      draw_color_selector(screen);
      SDL_Flip(screen);
      // save_colors(firstColor, secondColor);
    }

}

void draw_color_selector(SDL_Surface *screen)
{
    SDL_Rect position;
    SDL_Surface *a_block = NULL;
    SDL_Surface *b_block = NULL;

    position.x = 0;
    position.y = WINDOW_HEIGHT - 100;

    a_block = SDL_CreateRGBSurface(0, 100, WINDOW_WIDTH/2, 32, 0, 0, 0, 0);
    SDL_FillRect(a_block, NULL, SDL_MapRGB(a_block->format, config.left_eye_color.r, config.left_eye_color.g, config.left_eye_color.b));

    b_block = SDL_CreateRGBSurface(0, BLOCK_SIZE, BLOCK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(b_block, NULL, SDL_MapRGB(b_block->format, config.right_eye_color.r, config.right_eye_color.g, config.right_eye_color.b));

    SDL_BlitSurface(a_block, NULL, screen, &position);

    SDL_FreeSurface(a_block);
    SDL_FreeSurface(b_block);
}
