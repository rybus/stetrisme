#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdint.h>


#include "constants.h"
#include "play.h"

void freeScreenElements();
void print_selected_option(int selected_option, SDL_Surface *screen, SDL_Surface *right_arrow, SDL_Surface *black_block);

TTF_Font *font_title   = NULL;
TTF_Font *font_action = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *tetrisHome = NULL;
SDL_Surface *right_arrow = NULL;
SDL_Surface *title_text = NULL;
SDL_Surface *play_text = NULL;
SDL_Surface *configure_text = NULL;
SDL_Surface *black_block = NULL;

const int PLAY_OPTION = 0;
const int CONFIGURE_OPTION = 1;
int selected_option;

int main(int argc, char *argv[])
{
	SDL_Color white_color  = {255, 255, 255};
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Event event;
	int continuer = 1;
	SDL_Rect position;
	selected_option = PLAY_OPTION;

	screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (screen == NULL) {
		fprintf(stderr, "Unable to enable video mode : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(TTF_Init() == -1) {
		fprintf(stderr, "Error initializing TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	font_title  = TTF_OpenFont("resources/opensans.ttf", 65);
	font_action = TTF_OpenFont("resources/opensans.ttf", 30);
	title_text  = TTF_RenderText_Blended(font_title, "Stetrisme", white_color);
	play_text   = TTF_RenderText_Blended(font_action, "play", white_color);
	configure_text = TTF_RenderText_Blended(font_action, "configure", white_color);

	SDL_WM_SetCaption("Stetrisme", NULL);
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
				freeScreenElements();
				if (selected_option == PLAY_OPTION)
				{
					play(screen);
				}
				else
				{
					// configure(screen);
				}
				continuer = 0;
				break;
			default:
				break;
			}
			break;
		}

		SDL_Flip(screen);
	}

	SDL_Quit();
	TTF_Quit();

	return EXIT_SUCCESS;
}

void print_selected_option(int selected_option, SDL_Surface *screen, SDL_Surface *right_arrow, SDL_Surface *black_block)
{
	SDL_Rect position;
	position.x = 120;
	if (selected_option == PLAY_OPTION)
	{
		position.y = 200;
		SDL_BlitSurface(right_arrow, NULL, screen, &position);
		position.y = 250;
		SDL_BlitSurface(black_block, NULL, screen, &position);
	}
	else
 	{
		position.y = 250;
		SDL_BlitSurface(right_arrow, NULL, screen, &position);
		position.y = 200;
		SDL_BlitSurface(black_block, NULL, screen, &position);
	}
}

void freeScreenElements()
{
	SDL_FreeSurface(tetrisHome);
	SDL_FreeSurface(title_text);
	SDL_FreeSurface(play_text);
	SDL_FreeSurface(screen);
	TTF_CloseFont(font_title);
	TTF_CloseFont(font_action);
}
