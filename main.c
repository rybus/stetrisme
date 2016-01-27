#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "play.h"

void pause();

int main(int argc, char *argv[])
{
      SDL_Init(SDL_INIT_EVERYTHING);
      SDL_Surface *screen = NULL, *tetrisHome = NULL, *title_text = NULL, *play_text = NULL, *configure_text = NULL;
      SDL_Event event;
      int continuer = 1;
      SDL_Rect position;
      TTF_Font *font_title = NULL, *font_action;

      screen = SDL_SetVideoMode(640, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
      if (screen == NULL) {
         fprintf(stderr, "Unable to enable video mode : %s\n", SDL_GetError());
         exit(EXIT_FAILURE);
      }

      if(TTF_Init() == -1) {
          fprintf(stderr, "Error initializing TTF_Init : %s\n", TTF_GetError());
          exit(EXIT_FAILURE);
      }

      SDL_Color whiteColor = {255, 255, 255};
      font_title  = TTF_OpenFont("resources/opensans.ttf", 65);
      font_action = TTF_OpenFont("resources/opensans.ttf", 30);
      title_text  = TTF_RenderText_Blended(font_title, "Stetrisme", whiteColor);
      play_text   = TTF_RenderText_Blended(font_action, "Press ENTER to play", whiteColor);
      configure_text = TTF_RenderText_Blended(font_action, "Press ESC to configure", whiteColor);

      SDL_WM_SetCaption("Stetrisme", NULL);
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 17, 206, 112));


      tetrisHome = IMG_Load("pictures/tetris.png");
      SDL_BlitSurface(tetrisHome, NULL, screen, &position);

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
                        play(screen);
                        continuer = 0;
                        break;
                    case SDLK_ESCAPE:
                        // configure(screen);
                        continuer = 0;
                        break;
                }
                break;
        }
    
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(tetrisHome, NULL, screen, &position);

        position.x = 60;
        position.y = 10;
        SDL_BlitSurface(title_text, NULL, screen, &position);

        position.x = 200;
        position.y = 200;
        SDL_BlitSurface(play_text, NULL, screen, &position);  

        position.y = 300;
        SDL_BlitSurface(configure_text, NULL, screen, &position);  

        SDL_Flip(screen);
    }

    SDL_FreeSurface(tetrisHome);
    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}