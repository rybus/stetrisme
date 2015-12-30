#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void pause();

int main(int argc, char *argv[])
{
      SDL_Init(SDL_INIT_VIDEO);
      SDL_Surface *ecran = NULL, *tetrisHome = NULL;
      SDL_Event event;
      SDL_Rect position;
      int i;

      ecran = SDL_SetVideoMode(600, 800, 32, SDL_HWSURFACE);
      if (ecran == NULL)
      {
         fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
         exit(EXIT_FAILURE);
      }
      SDL_WM_SetCaption("Stetrisme", NULL);
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));


      position.x = 0;
      position.y = i;
      tetrisHome = IMG_Load("pictures/tetris.png");
      SDL_BlitSurface(tetrisHome, NULL, ecran, &position);


      SDL_Flip(ecran);

      pause();
      SDL_FreeSurface(tetrisHome);
      SDL_Quit();

      return EXIT_SUCCESS;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
