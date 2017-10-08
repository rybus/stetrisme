#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>
#include <errno.h>

#include "constants.h"
#include "draw_game.h"
#include "grid.h"
#include "tetromino.h"
#include "config.h"
#include "events.h"
#include "play.h"

Config_t config;
Tetromino_t tetromino;
Block grid[HORIZONTAL_BLOCK_NB][VERTICAL_BLOCK_NB];
Input in;
int score, level, current_time, previous_time, next_tetromino_type, nb_fallen_blocks, color_reversed;

void play(SDL_Surface *screen)
{
    current_time = previous_time = nb_fallen_blocks = color_reversed = 0;

    config = load_config();
    memset(&in, 0, sizeof(in));
    score = level = 0;
    initialize_game(grid);
    initialize_color_blocks(config);
    tetromino = next_tetromino(grid, &score, &next_tetromino_type);

    while(!in.key[SDLK_ESCAPE])
    {
        UpdateEvents(&in);

        if (in.key[SDLK_LEFT])
        {
            if (can_move_left(grid, tetromino))
                move_left(&tetromino);
            in.key[SDLK_LEFT] = 0;
        }
        if (in.key[SDLK_RIGHT])
        {
            if (can_move_right(grid, tetromino))
                move_right(&tetromino);
            in.key[SDLK_RIGHT] = 0;
        }
        if (in.key[SDLK_DOWN])
        {
            if (can_move_down(grid, tetromino))
            {
                move_down(&tetromino);
            }
            else
            {
                block_current_tetromino(grid, tetromino);
                tetromino = next_tetromino(grid, &score, &next_tetromino_type);
                nb_fallen_blocks++;
                if (nb_fallen_blocks % COLOR_SWITCH_NB_FALLEN_BLOCK == 0)
                {
                    color_reversed = !color_reversed;
                }
                if (!can_be_placed(grid, tetromino))
                {
                    in.key[SDLK_ESCAPE] = 1;
                    continue;
                }
            }
            in.key[SDLK_DOWN] = 0;
        }

        if (in.key[SDLK_q] && can_rotate_counter_clockwise(grid, tetromino))
        {
            rotate_counter_clockwise(&tetromino);
            in.key[SDLK_q] = 0;
        }
        if (in.key[SDLK_s] && can_rotate_clockwise(grid, tetromino))
        {
            rotate_clockwise(&tetromino);
            in.key[SDLK_s] = 0;
        }

        if (in.key[SDLK_SPACE])
        {
            while (can_move_down(grid, tetromino))
                move_down(&tetromino);

            block_current_tetromino(grid, tetromino);
            tetromino = next_tetromino(grid, &score, &next_tetromino_type);
            nb_fallen_blocks++;
            if (nb_fallen_blocks % COLOR_SWITCH_NB_FALLEN_BLOCK == 0)
            {
                color_reversed = !color_reversed;
            }
            if (!can_be_placed(grid, tetromino))
            {
                in.key[SDLK_ESCAPE] = 1;
                continue;
            }
            in.key[SDLK_SPACE] = 0;
        }

        current_time = SDL_GetTicks();
        if (current_time - previous_time > get_speed(level))
        {
            if (can_move_down(grid, tetromino))
            {
                move_down(&tetromino);
            }
            else
            {
                block_current_tetromino(grid, tetromino);
            }
            previous_time = current_time;
        }

        if (score > config.high_score)
        {
            config.high_score = score;
            save_config(config);
        }

        draw_game(screen, grid, tetromino, next_tetromino_type, config, score, level, color_reversed);
    }
}

int get_speed(int level)
{
    return DEFAULT_SPEED_MS - level*50;
}
