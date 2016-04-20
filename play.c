#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constants.h"
#include "generator.h"
#include "play.h"

int score = 1;
int level = 1;
int keepPlaying = 1;
int max_score   = 9999;
int previousTime = 0;
int currentTime  = 0;


SDL_Event playEvent;
SDL_Surface *play_surface = NULL;
TTF_Font *label_font   = NULL;
TTF_Font *regular_font = NULL;
SDL_Surface *green_block = NULL;
SDL_Surface *red_block = NULL;
SDL_Surface *black_block = NULL;
SDL_Color white_color  = {255, 255, 255};
SDL_Color fushia_color = {0, 152, 247};

int play(SDL_Surface *screen)
{
    regular_font = TTF_OpenFont("resources/opensans.ttf", 20);
    label_font = TTF_OpenFont("resources/opensans.ttf", 30);
    black_block = IMG_Load("pictures/black_block.png");
    green_block = IMG_Load("pictures/green_block.png");
    red_block = IMG_Load("pictures/red_block.png");
    block_types grid[WIDTH_BLOCK_NB][HEIGHT_BLOCK_NB];

   init_game(grid);

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
                            if (isLeftMovable(grid)) {
                                moveLeft(grid);
                            }
                        break;
                        case SDLK_RIGHT:
                            if (isRightMovable(grid)) {
                                moveRight(grid);
                            }
                        break;
                        case SDLK_DOWN:
                            if (isDownMovable(grid)) {
                                moveDown(grid);
                            }
                        break;
                        default:
                        break;
                    }
                break;
            }
        }

        currentTime = SDL_GetTicks();
        if (currentTime - previousTime > 500)
        {
            // moveDown();
            previousTime = currentTime;
        }

        draw_game_set(screen, score, level, max_score);
        draw_game(screen, grid);
        SDL_Flip(screen);
    }


    return EXIT_SUCCESS;
}

void init_game(block_types grid[][HEIGHT_BLOCK_NB])
{
    int x, y;
    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
             grid[x][y] = EMPTY;
        }
    }
    nextTetrino(grid);
}

void nextTetrino(block_types grid[][HEIGHT_BLOCK_NB])
{
    int tetrino[4][4];
    int x, y;
    get_next_tetrimino(tetrino);

    for(x = (WIDTH_BLOCK_NB/2); x < (WIDTH_BLOCK_NB/2)+4; x++) {
        for (y = 0; y < 4; y++) {
          if (tetrino[x - (WIDTH_BLOCK_NB/2)][y] == 1) {
                grid[x][y] = CURRENT;
          }
        }
    }

}

void draw_game(SDL_Surface *screen, block_types grid[][HEIGHT_BLOCK_NB])
{
    int x, y;
    SDL_Rect position;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
            position.x = x * BLOCK_SIZE;
            position.y = y * BLOCK_SIZE;

            if(grid[x][y] == BLOCK) {
                SDL_BlitSurface(red_block, NULL, screen, &position);
            } else if (grid[x][y] == CURRENT) {
                SDL_BlitSurface(green_block, NULL, screen, &position);
            } else {
                SDL_BlitSurface(black_block, NULL, screen, &position);
            }
        }
    }
}

int isLeftMovable(block_types grid[][HEIGHT_BLOCK_NB])
{
    int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
            if (grid[x][y] == CURRENT) {
                if (x - 1 < 0) {

                    return 0;
                } else if (grid[x - 1][y] == BLOCK) {

                    return 0;
                }
            }
        }
    }

    return 1;
}

int isRightMovable(block_types grid[][HEIGHT_BLOCK_NB])
{
    int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
           if (grid[x][y] == CURRENT) {
                if (x + 1 > WIDTH_BLOCK_NB) {

                    return 0;
                } else if (grid[x + 1][y] == BLOCK) {

                    return 0;
                }
            }
        }
    }

    return 1;
}

int isDownMovable(block_types grid[][HEIGHT_BLOCK_NB])
{
    int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB - 1; y++) {
           if (grid[x][y] == CURRENT) {
                if (y + 1 > HEIGHT_BLOCK_NB) {

                    return 0;
                } else if (grid[x][y + 1] == BLOCK) {

                    return 0;
                }
            }
        }
    }

    return 1;
}

void moveDown(block_types grid[][HEIGHT_BLOCK_NB])
{
    int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = HEIGHT_BLOCK_NB - 1; y > 0; y--) {
            if (grid[x][y] == CURRENT) {
                grid[x][y + 1] = CURRENT;
                grid[x][y] = EMPTY;
            }
        }
    }
}

void moveLeft(block_types grid[][HEIGHT_BLOCK_NB])
{
    int x, y;

    for(x = 0; x < WIDTH_BLOCK_NB; x++) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
            if (grid[x][y] == CURRENT) {
                grid[x - 1][y] = CURRENT;
                grid[x][y] = EMPTY;
            }
        }
    }
}

void moveRight(block_types grid[][HEIGHT_BLOCK_NB])
{
    int x, y;

    for(x = WIDTH_BLOCK_NB - 1; x > 0 ; x--) {
        for (y = 0; y < HEIGHT_BLOCK_NB; y++) {
            if (grid[x][y] == CURRENT) {
                grid[x + 1][y] = CURRENT;
                grid[x][y] = EMPTY;
            }
        }
    }
}

/*
* Draws game set
*
* @param int score     current score
* @param int level     current level
* @param int max_score max score. ever
*/
void draw_game_set(SDL_Surface *screen, int score, int level, int max_score)
{
    SDL_Rect position;
    char score_label_text[6]          = "score";
    char maximum_score_label_text[11] = "max. score";
    char current_level_label_text[6]  = "level";

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
void print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position)
{
    SDL_Surface *label_surface  = NULL;
    SDL_Surface *number_surface = NULL;
    char number_text[10];

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
void erase_surface(SDL_Surface *surface)
{
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
}
