#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constants.h"
#include "play.h"

int score = 1;
int level = 1;
int keepPlaying = 1;
int max_score   = 9999;
int previousTime = 0;
int currentTime  = 0;
char score_label_text[6]          = "score";
char maximum_score_label_text[11] = "max. score";
char current_level_label_text[6]  = "level";
char number_text[10];     


SDL_Event playEvent;
SDL_Surface *playArea    = NULL;
SDL_Surface *green_block = NULL;
SDL_Rect block_position;
SDL_Color white_color  = {255, 255, 255};
SDL_Color fushia_color = {0, 152, 247};
TTF_Font *label_font   = NULL;
TTF_Font *regular_font = NULL;

int play(SDL_Surface *screen)
{
    label_font   = TTF_OpenFont("resources/opensans.ttf", 30);
    regular_font = TTF_OpenFont("resources/opensans.ttf", 20);
    green_block = IMG_Load("pictures/green_block.png");

    while (keepPlaying)
    {
      while(SDL_PollEvent(&playEvent)) 
      {
        switch(playEvent.type)
        {
            case SDL_QUIT:
                keepPlaying = 0;
                break;
            case SDL_KEYDOWN:
                switch(playEvent.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        keepPlaying = 0;
                        break;
                    case SDLK_F1:
                        score++;
                        break;
                    case SDLK_LEFT:
                        block_position.x = block_position.x - BLOCK_SIZE;
                        break;
                    case SDLK_RIGHT:
                        block_position.x = block_position.x + BLOCK_SIZE;
                        break;
                    case SDLK_DOWN:
                        block_position.y = block_position.y + BLOCK_SIZE;
                        break;
                }
                break;
        }
      }

      currentTime = SDL_GetTicks();
      if (currentTime - previousTime > 500)
      {
          block_position.y = block_position.y + BLOCK_SIZE;
          previousTime = currentTime; 
      } 
    
      draw_game_set(screen, score, level, max_score);
      draw_game(screen, block_position, green_block);
      SDL_Flip(screen);
    }


    return EXIT_SUCCESS;
}

int draw_game(SDL_Surface *screen, SDL_Rect position, SDL_Surface *block)
{
    SDL_BlitSurface(block, NULL, screen, &position); 
}

/*
 * Draws game set
 * 
 * @param int score     current score
 * @param int level     current level
 * @param int max_score max score. ever 
 */
int draw_game_set(SDL_Surface *screen, int score, int level, int max_score)
{
  SDL_Rect position;

  erase_surface(screen);

  position.x = 450;
  position.y = 200;
  print_integer_informations(screen, score_label_text, score, &position);

  position.y = position.y + 80;
  print_integer_informations(screen, maximum_score_label_text, max_score, &position);
  position.y = position.y + 80;
  print_integer_informations(screen, current_level_label_text, level, &position);
}

/*
 * Displays integer informations such as score, max. score or level.
 * 
 * @param SDL_Surface surface
 * @param char *label the label of the information
 * @param int number the information itself
 */
int print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position)
{
  SDL_Surface *label_surface  = NULL;
  SDL_Surface *number_surface = NULL;

  sprintf(number_text, "%d", number);
  
  label_surface  = TTF_RenderText_Blended(label_font, label, white_color);
  SDL_BlitSurface(label_surface, NULL, screen, position);
  
  position->y = position->y + 40;
  number_surface = TTF_RenderText_Blended(regular_font, number_text, fushia_color);
  SDL_BlitSurface(number_surface, NULL, screen, position);
}

/*
 * Erases the surface with black
 *
 * @param SDL_Surface the surface to erase
 */
int erase_surface(SDL_Surface *surface)
{
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
}