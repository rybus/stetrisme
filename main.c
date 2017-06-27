#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdint.h>

#include "menu.h"
#include "constants.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen = NULL;
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        fprintf(stderr, "Unable to enable video mode : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Error initializing TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Stetrisme", NULL);
    menu(screen);

    SDL_FreeSurface(screen);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
