#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <errno.h>

#include "constants.h"
#include "config.h"
#include "configure.h"
#include "events.h"
#include "play.h"
#include "draw_game.h"

Config_t config;
int currentPosition;
TTF_Font *font;

void configure(SDL_Surface *screen)
{
    Color_t *left_eye_color_ptr, *right_eye_color_ptr;
    int *selectors[6];
    font = TTF_OpenFont("resources/opensans.ttf", 20);
    Input in;

    memset(&in, 0, sizeof(in));
    config = load_config();

    left_eye_color_ptr = &config.left_eye_color;
    right_eye_color_ptr = &config.right_eye_color;

    erase_surface(screen);
    currentPosition = 0;

    selectors[0] = &(*left_eye_color_ptr).r;
    selectors[1] = &(*left_eye_color_ptr).g;
    selectors[2] = &(*left_eye_color_ptr).b;
    selectors[3] = &(*right_eye_color_ptr).r;
    selectors[4] = &(*right_eye_color_ptr).g;
    selectors[5] = &(*right_eye_color_ptr).b;

    while(!in.key[SDLK_ESCAPE])
    {
        UpdateEvents(&in);
        if (in.key[SDLK_LEFT]) {
            if (currentPosition > 0) {
                currentPosition--;
            }
            in.key[SDLK_LEFT] = 0;
        }
        if (in.key[SDLK_RIGHT]) {
            if (currentPosition < 6) {
                currentPosition++;
            }
            in.key[SDLK_RIGHT] = 0;
        }
        if (in.key[SDLK_UP]) {
            if (*selectors[currentPosition] == 255)
                *selectors[currentPosition] = 0;
            else
                (*selectors[currentPosition])++;
            in.key[SDLK_UP] = 0;
        }
        if (in.key[SDLK_DOWN]) {
            if (*selectors[currentPosition] == 0)
                *selectors[currentPosition] = 255;
            else
                (*selectors[currentPosition])--;
            in.key[SDLK_DOWN] = 0;
        }

        erase_surface(screen);
        draw_color_selector(screen);
        SDL_Flip(screen);
    }

    save_config(config);
}

void draw_color_selector(SDL_Surface *screen)
{
    SDL_Rect position;
    SDL_Surface *a_block, *b_block, *left_eye_color, *right_eye_color;
    SDL_Color white_color  = {255, 255, 255};

    char left_eye_color_txt[18], right_eye_color_txt[18];

    sprintf(
        left_eye_color_txt,
        "r:%d g:%d b:%d",
        config.left_eye_color.r,
        config.left_eye_color.g,
        config.left_eye_color.b
    );
    sprintf(
        right_eye_color_txt,
        "r:%d g:%d b:%d",
        config.right_eye_color.r,
        config.right_eye_color.g,
        config.right_eye_color.b
    );

    position.x = 170;
    position.y = 100;

    left_eye_color = TTF_RenderText_Blended(
        font,
        left_eye_color_txt,
        white_color
    );
    right_eye_color = TTF_RenderText_Blended(
        font,
        right_eye_color_txt,
        white_color
    );
    position.x = 100;
    position.y = 200;

    SDL_BlitSurface(left_eye_color, NULL, screen, &position);
    position.x += 200;
    SDL_BlitSurface(right_eye_color, NULL, screen, &position);

    position.x = 100;
    position.y = WINDOW_HEIGHT - 200;

    a_block = SDL_CreateRGBSurface(0, BLOCK_SIZE*4, BLOCK_SIZE*4, 32, 0, 0, 0, 0);
    SDL_FillRect(
        a_block,
        NULL,
        SDL_MapRGB(
            a_block->format,
            config.left_eye_color.r,
            config.left_eye_color.g,
            config.left_eye_color.b
        )
    );

    b_block = SDL_CreateRGBSurface(0, BLOCK_SIZE*4, BLOCK_SIZE*4, 32, 0, 0, 0, 0);
    SDL_FillRect(
        b_block,
        NULL,
        SDL_MapRGB(
            b_block->format,
            config.right_eye_color.r,
            config.right_eye_color.g,
            config.right_eye_color.b
        )
    );

    SDL_BlitSurface(a_block, NULL, screen, &position);

    position.x += 200;
    SDL_BlitSurface(b_block, NULL, screen, &position);

    SDL_FreeSurface(a_block);
    SDL_FreeSurface(b_block);
    SDL_FreeSurface(right_eye_color);
    SDL_FreeSurface(left_eye_color);
}
