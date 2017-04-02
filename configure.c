#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <errno.h>
#include <libconfig.h>

#include "constants.h"
#include "colors.h"
#include "configure.h"
#include "events.h"
#include "play.h"

void configure(SDL_Surface *screen)
{
  struct color firstColor, secondColor, *firstColorPtr, *secondColorPtr;
  firstColorPtr = &firstColor;
  secondColorPtr = &secondColor;

  int *selectors[6];
  int currentPosition;
  Input in;

  memset(&in, 0, sizeof(in));
  load_colors(firstColorPtr, secondColorPtr);
  erase_surface(screen);
  currentPosition = 0;

  selectors[0] = &(*firstColorPtr).r;
  selectors[1] = &(*firstColorPtr).g;
  selectors[2] = &(*firstColorPtr).b;
  selectors[3] = &(*secondColorPtr).r;
  selectors[4] = &(*secondColorPtr).g;
  selectors[5] = &(*secondColorPtr).b;

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

      draw_color_selector(screen, firstColor, secondColor, currentPosition);
      SDL_Flip(screen);
      save_colors(firstColor, secondColor);
    }

}

void draw_color_selector(SDL_Surface *screen, struct color firstColor, struct color secondColor, int currentPosition)
{
    SDL_Rect position;
    SDL_Surface *a_block = NULL;
    SDL_Surface *b_block = NULL;

    position.x = 0;
    position.y = WINDOW_HEIGHT - 100;

    a_block = SDL_CreateRGBSurface(0, 100, WINDOW_WIDTH/2, 32, 0, 0, 0, 0);
    SDL_FillRect(a_block, NULL, SDL_MapRGB(a_block->format, firstColor.r, firstColor.g, firstColor.b));

    b_block = SDL_CreateRGBSurface(0, BLOCK_SIZE, BLOCK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(b_block, NULL, SDL_MapRGB(b_block->format, secondColor.r, secondColor.g, secondColor.b));

    SDL_BlitSurface(a_block, NULL, screen, &position);

    SDL_FreeSurface(a_block);
    SDL_FreeSurface(b_block);
}
