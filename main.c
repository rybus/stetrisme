#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdint.h>

#include "constants.h"
#include "play.h"

void freeScreenElements();

TTF_Font *font_title   = NULL;
TTF_Font *font_action = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *tetrisHome = NULL;
SDL_Surface *title_text = NULL;
SDL_Surface *play_text = NULL;

int main(int argc, char *argv[])
{
	SDL_Color white_color  = {255, 255, 255};
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Event event;
	int continuer = 1;
	SDL_Rect position;

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
	play_text   = TTF_RenderText_Blended(font_action, "Press ENTER to play", white_color);

	SDL_WM_SetCaption("Stetrisme", NULL);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	tetrisHome = IMG_Load("resources/pictures/tetris.png");

	position.x = 0;
	position.y = 0;
	SDL_BlitSurface(tetrisHome, NULL, screen, &position);

	position.x = 60;
	position.y = 10;
	SDL_BlitSurface(title_text, NULL, screen, &position);

	position.x = 200;
	position.y = 200;
	SDL_BlitSurface(play_text, NULL, screen, &position);

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
			case SDLK_RETURN:
				freeScreenElements();
				play(screen);
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

void freeScreenElements()
{
	SDL_FreeSurface(tetrisHome);
	SDL_FreeSurface(title_text);
	SDL_FreeSurface(play_text);
	SDL_FreeSurface(screen);
	TTF_CloseFont(font_title);
	TTF_CloseFont(font_action);
}
