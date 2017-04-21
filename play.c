#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <errno.h>
#include <libconfig.h>

#include "constants.h"
#include "block_creations.h"
#include "block_movements.h"
#include "block_rotations.h"
#include "play.h"
#include "config.h"
#include "events.h"

Config_t config;
Input in;
Block grid[HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS][VERTICAL_BLOCK_NB];
Block current_grid[HORIZONTAL_BLOCK_NB + 2 * EXTRA_BLOCKS][VERTICAL_BLOCK_NB];
SDL_Surface *a_block, *b_block, *background;

int score, level, clear_lines, current_time, previous_time, cleared_lines;

void play(SDL_Surface *screen)
{
    score = current_time = previous_time = cleared_lines = level = 0;

    config = load_config();

    background = SDL_CreateRGBSurface(0, BLOCK_SIZE, BLOCK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 0, 0, 0));

    a_block = SDL_CreateRGBSurface(0, BLOCK_SIZE, BLOCK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(a_block,
        NULL,
        SDL_MapRGB(
            a_block->format,
            config.left_eye_color.r,
            config.left_eye_color.g,
            config.left_eye_color.b
        )
    );

    b_block = SDL_CreateRGBSurface(0, BLOCK_SIZE, BLOCK_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect(b_block,
        NULL,
        SDL_MapRGB(
            b_block->format,
            config.right_eye_color.r,
            config.right_eye_color.g,
            config.right_eye_color.b
        )
    );

    memset(&in, 0, sizeof(in));

    initialize_game();

    while(!in.key[SDLK_ESCAPE]) {
        UpdateEvents(&in);
        if (in.key[SDLK_LEFT]) {
            moveLeft(current_grid, grid);
            in.key[SDLK_LEFT] = 0;
        }
        if (in.key[SDLK_RIGHT]) {
            moveRight(current_grid, grid);
            in.key[SDLK_RIGHT] = 0;
        }
        if (in.key[SDLK_DOWN]) {
            if(moveDown(current_grid, grid, &score, &level, &cleared_lines) == 0) {
                in.key[SDLK_ESCAPE] = 1;
            }
            in.key[SDLK_DOWN] = 0;
        }
        if (in.key[SDLK_q]) {
            rotateCounterClockWise(grid, current_grid);
            in.key[SDLK_q] = 0;
        }
        if (in.key[SDLK_SPACE]) {
            if (!moveFullDown(current_grid, grid, &score, &level, &cleared_lines))
                in.key[SDLK_ESCAPE] = 1;
            in.key[SDLK_SPACE] = 0;
        }
        if (in.key[SDLK_s]) {
            rotateClockWise(grid, current_grid);
            in.key[SDLK_s] = 0;
        }

        current_time = SDL_GetTicks();
        if (current_time - previous_time > get_speed(level)) {
            if (!moveDown(current_grid, grid, &score, &level, &cleared_lines))
                in.key[SDLK_ESCAPE] = 1;
            previous_time = current_time;
        }

        if (score > config.high_score) {
          config.high_score = score;
          save_config(config);
        }

        draw_game(screen);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(a_block);
    SDL_FreeSurface(b_block);
    SDL_FreeSurface(background);
}

int get_speed(int level)
{
  return DEFAULT_SPEED_MS - level*50;
}

void initialize_game()
{
    for(int x = 0; x < HORIZONTAL_BLOCK_NB + 2*EXTRA_BLOCKS; x++) {
        for (int y = 0; y < VERTICAL_BLOCK_NB; y++) {
            current_grid[x][y] = EMPTY;
            if (x >= EXTRA_BLOCKS && x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS)
                grid[x][y] = EMPTY;
            else
                grid[x][y] = BORDER_BLOCK;
        }
    }

    next_tetromino(current_grid, grid, &score, &level, &cleared_lines);
}

void draw_game(SDL_Surface *screen)
{
    SDL_Rect position;
    char score_label_text[6]          = "score";
    char maximum_score_label_text[11] = "max. score";
    char current_level_label_text[6]  = "level";

    erase_surface(screen);
    draw_game_borders(screen);

    position.x = GAME_AREA_WIDTH + 10;
    position.y = 70;
    print_integer_informations(screen, score_label_text, score, &position);

    position.y += 80;
    print_integer_informations(screen, maximum_score_label_text, config.high_score, &position);
    position.y += 80;
    print_integer_informations(screen, current_level_label_text, level, &position);

    draw_tetrominos(screen);
}

void draw_tetrominos(SDL_Surface *screen)
{
    SDL_Rect position;
    for (int x = EXTRA_BLOCKS; x < HORIZONTAL_BLOCK_NB + EXTRA_BLOCKS; x++) {
        for (int y = 2; y < VERTICAL_BLOCK_NB; y++) {
            position.x = (x - EXTRA_BLOCKS) * BLOCK_SIZE + GAME_BORDER_WIDTH;
            position.y = (y - 2) * BLOCK_SIZE + GAME_BORDER_WIDTH;

            if(grid[x][y] == BLOCK)
                SDL_BlitSurface(a_block, NULL, screen, &position);
            else if (current_grid[x][y] == CURRENT)
                SDL_BlitSurface(b_block, NULL, screen, &position);
            else
                SDL_BlitSurface(background, NULL, screen, &position);
        }
    }
}
void draw_game_borders(SDL_Surface *screen)
{
    Pixel_t white_pixel;
    white_pixel.r = white_pixel.g = white_pixel.b = (Uint8) 0xff;
    white_pixel.alpha = (Uint8) 128;

    SDL_LockSurface(screen);

    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            // top border
            if (y < GAME_BORDER_WIDTH && x < GAME_AREA_WIDTH)
                put_pixel(screen, x, y, &white_pixel);

            // bottom border
            if (y > WINDOW_HEIGHT - GAME_BORDER_WIDTH*2 && x < GAME_AREA_WIDTH)
                put_pixel(screen, x, y, &white_pixel);

            // left and right borders
            if (x < GAME_BORDER_WIDTH) {
                put_pixel(screen, x, y, &white_pixel);
                put_pixel(screen, GAME_AREA_WIDTH - GAME_BORDER_WIDTH + x, y, &white_pixel);
            }
        }
    }

    SDL_UnlockSurface(screen);
}

/**
 * Draws a signel Pixel_t on the screen at the (x, y) position.
 */
void put_pixel(SDL_Surface* screen, int x, int y, Pixel_t* p)
{
    Uint32* p_screen = (Uint32*) screen->pixels;
    p_screen += y*screen->w+x;
    *p_screen = SDL_MapRGBA(screen->format, p->r, p->g, p->b, p->alpha);
}

/**
* Displays integer informations such as score, max. score or level.
*
* @param SDL_Surface surface
* @param char *label the label of the information
* @param int number the information itself
*/
void print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position)
{
    TTF_Font *label_font, *regular_font;
    char number_text[10];
    SDL_Color white_color  = {255, 255, 255};
    SDL_Color fushia_color = {0, 152, 247};
    SDL_Surface *label_surface, *number_surface;

    sprintf(number_text, "%d", number);
    regular_font = TTF_OpenFont("resources/opensans.ttf", 20);
    label_font = TTF_OpenFont("resources/opensans.ttf", 30);

    label_surface = TTF_RenderText_Blended(label_font, label, white_color);
    SDL_BlitSurface(label_surface, NULL, screen, position);

    position->y = position->y + 40;
    number_surface = TTF_RenderText_Blended(regular_font, number_text, fushia_color);
    SDL_BlitSurface(number_surface, NULL, screen, position);

    TTF_CloseFont(regular_font);
    TTF_CloseFont(label_font);
    SDL_FreeSurface(number_surface);
    SDL_FreeSurface(label_surface);
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
