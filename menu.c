#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdint.h>

#include "constants.h"
#include "configure.h"
#include "play.h"
#include "menu.h"
#include "events.h"

int menu(SDL_Surface *screen)
{
    Input in;
    int continuer = 1;
    int selected_option = PLAY_OPTION;
    memset(&in, 0, sizeof(in));

    while(!in.key[SDLK_ESCAPE])
    {
        UpdateEvents(&in);
        print_menu(screen, selected_option);

        if (in.key[SDLK_DOWN] || in.key[SDLK_UP]) {
            selected_option = !selected_option;
            in.key[SDLK_DOWN] = 0;
            in.key[SDLK_UP] = 0;
        }

        if (in.key[SDLK_RETURN])
        {
            if (selected_option == PLAY_OPTION)
            {
                play(screen);
            }
            else
            {
                configure(screen);
            }
            in.key[SDLK_RETURN] = 0;
        }
        SDL_Flip(screen);
    }
}

void print_menu(SDL_Surface *screen, int selected_option)
{
    TTF_Font *font_title, *font_action;
    SDL_Surface *tetrisHome, *right_arrow, *title_text;
    SDL_Surface *play_text, *configure_text, *black_block;
    SDL_Rect position;
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

    position.x = position.y = 0;
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

    SDL_FreeSurface(black_block);
    SDL_FreeSurface(tetrisHome);
    SDL_FreeSurface(right_arrow);
    SDL_FreeSurface(title_text);
    SDL_FreeSurface(play_text);
    SDL_FreeSurface(configure_text);
    TTF_CloseFont(font_title);
    TTF_CloseFont(font_action);
}

void print_selected_option(int selected_option, SDL_Surface *screen, SDL_Surface *right_arrow, SDL_Surface *black_block)
{
    SDL_Rect position;
    position.x = 130;
    position.y = 255;
    if (selected_option == PLAY_OPTION)
    {
        SDL_BlitSurface(black_block, NULL, screen, &position);
        position.y = 205;
        SDL_BlitSurface(right_arrow, NULL, screen, &position);
    }
    else
    {
        SDL_BlitSurface(right_arrow, NULL, screen, &position);
        position.y = 205;
        SDL_BlitSurface(black_block, NULL, screen, &position);
    }
}
