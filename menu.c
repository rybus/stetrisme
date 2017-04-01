#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdint.h>

#include "configure.h"
#include "constants.h"
#include "play.h"
#include "menu.h"

int menu(SDL_Surface *screen)
{
  TTF_Font *font_title   = NULL;
  TTF_Font *font_action = NULL;
  SDL_Surface *tetrisHome = NULL;
  SDL_Surface *right_arrow = NULL;
  SDL_Surface *title_text = NULL;
  SDL_Surface *play_text = NULL;
  SDL_Surface *configure_text = NULL;
  SDL_Surface *black_block = NULL;
  SDL_Event event;
  int continuer = 1;
  SDL_Rect position;
  int selected_option = PLAY_OPTION;

	SDL_Color white_color  = {255, 255, 255};

  font_title  = TTF_OpenFont("resources/opensans.ttf", 65);
  font_action = TTF_OpenFont("resources/opensans.ttf", 30);
  title_text  = TTF_RenderText_Blended(font_title, "Stetrisme", white_color);
  play_text   = TTF_RenderText_Blended(font_action, "play", white_color);
  configure_text = TTF_RenderText_Blended(font_action, "configure", white_color);

  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
  black_block = SDL_CreateRGBSurface(0, 40, 40, 32, 0, 0, 0, 0);
  SDL_FillRect(black_block, NULL, SDL_MapRGB(black_block->format,0, 0, 0));

  tetrisHome = IMG_Load("resources/pictures/tetris.png");
  right_arrow = IMG_Load("resources/pictures/right_arrow.png");

  position.x = 0;
  position.y = 0;
  SDL_BlitSurface(tetrisHome, NULL, screen, &position);

  position.x = 60;
  position.y = 10;
  SDL_BlitSurface(title_text, NULL, screen, &position);

  position.x = 170;
  position.y = 200;
  SDL_BlitSurface(play_text, NULL, screen, &position);

  position.x = 170;
  position.y = 250;
  SDL_BlitSurface(configure_text, NULL, screen, &position);

  // factoriser pour avoir une méthode "drawMenu(screen)" afin de pouvoir l'appeler à n'importe quel moment.

  print_selected_option(selected_option, screen, right_arrow, black_block);

  while (continuer)
  {
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
      continuer = 0;
      break;
      case SDL_KEYDOWN:
      switch(event.key.keysym.sym)
      {
        case SDLK_DOWN:
        case SDLK_UP:
        selected_option = !selected_option;
        print_selected_option(selected_option, screen, right_arrow, black_block);
        break;
        case SDLK_RETURN:
        // freeScreenElements();
        if (selected_option == PLAY_OPTION)
        {
          play(screen);
        }
        else
        {
          configure(screen);
        }
        break;
        default:
        break;
      }
      break;
    }

    SDL_Flip(screen);
  }
}


void print_selected_option(int selected_option, SDL_Surface *screen, SDL_Surface *right_arrow, SDL_Surface *black_block)
{
	SDL_Rect position;
	position.x = 130;
	if (selected_option == PLAY_OPTION)
	{
		position.y = 205;
		SDL_BlitSurface(right_arrow, NULL, screen, &position);
		position.y = 255;
		SDL_BlitSurface(black_block, NULL, screen, &position);
	}
	else
 	{
		position.y = 255;
		SDL_BlitSurface(right_arrow, NULL, screen, &position);
		position.y = 205;
		SDL_BlitSurface(black_block, NULL, screen, &position);
	}
}
