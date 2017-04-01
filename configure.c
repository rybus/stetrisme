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

int configure(SDL_Surface *screen)
{
  struct color first_color, second_color;

  load_colors(&first_color, &second_color);
  first_color.r = 9;
  first_color.g = 211;
  first_color.b = 0;

  second_color.r = 0;
  second_color.g = 2;
  second_color.b = 3;

  save_colors(first_color, second_color);
}
