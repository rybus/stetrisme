#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "constants.h"
#include "grid.h"
#include "tetromino.h"

int cleared_lines, next_tetromino_type, level;

int line_factors[4] =
{
    ONE_LINE_FACTOR,
    TWO_LINES_FACTOR,
    THREE_LINES_FACTOR,
    FOUR_LINES_FACTOR
};

void initialize_game(Block grid[][VERTICAL_BLOCK_NB])
{
    for (int x = 0; x < HORIZONTAL_BLOCK_NB; x++)
    {
        for (int y = 0; y < VERTICAL_BLOCK_NB; y++)
            grid[x][y] = EMPTY;
    }
}

Tetromino_t next_tetromino(Block grid[][VERTICAL_BLOCK_NB], int *score, int *next_tetromino_type)
{
    Tetromino_t tetromino;
    int current_tetromino_type = *next_tetromino_type;
    srand(time(NULL));
    *next_tetromino_type = rand() % 7;

    remove_full_lines(grid, score);
    tetromino = get_tetromino(current_tetromino_type);

    return tetromino;
}

int block_current_tetromino(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
    int tetromino_x, tetromino_y;

    // places the tetromino
    for (int x = tetromino.pos.x; x < tetromino.pos.x + TETROMINO_LENGTH; x++)
    {
        for (int y = tetromino.pos.y; y < tetromino.pos.y + TETROMINO_LENGTH; y++)
        {
            tetromino_x = x - tetromino.pos.x;
            tetromino_y = y - tetromino.pos.y;
            if (tetromino.block[tetromino_x][tetromino_y] == CURRENT_BLOCK)
                grid[x][y] = FIXED_BLOCK;
        }
    }
}

int place_current_tetromino(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
    int tetromino_x, tetromino_y;

    if (!can_be_placed(grid, tetromino))
        return 0;

    // clears current grid
    for (int x = 0; x < HORIZONTAL_BLOCK_NB; x++)
    {
        for (int y = 0; y < VERTICAL_BLOCK_NB; y++)
        {
            if (grid[x][y] == CURRENT_BLOCK)
                grid[x][y] = EMPTY;
        }
    }

    // places the tetromino
    for (int x = tetromino.pos.x; x < tetromino.pos.x + TETROMINO_LENGTH; x++)
    {
        for (int y = tetromino.pos.y; y < tetromino.pos.y + TETROMINO_LENGTH; y++)
        {
            tetromino_x = x - tetromino.pos.x;
            tetromino_y = y - tetromino.pos.y;
            if (tetromino.block[tetromino_x][tetromino_y] == CURRENT_BLOCK)
                grid[x][y] = FIXED_BLOCK;
        }
    }

    return 1;
}

int can_be_placed(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
    int x, y;
    int tetromino_x, tetromino_y;

    for (x = tetromino.pos.x; x < tetromino.pos.x + TETROMINO_LENGTH; x++)
    {
        for (y = tetromino.pos.y; y < tetromino.pos.y + TETROMINO_LENGTH; y++)
        {
            tetromino_x = x - tetromino.pos.x;
            tetromino_y = y - tetromino.pos.y;
            if (tetromino.block[tetromino_x][tetromino_y] == CURRENT_BLOCK)
            {
                if (x < 0 || x >= HORIZONTAL_BLOCK_NB || y >= VERTICAL_BLOCK_NB)
                    return 0;

                if (grid[x][y] == FIXED_BLOCK)
                    return 0;
            }
        }
    }

    return 1;
}

int can_move_down(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
    Tetromino_t tested_tetromino = tetromino;
    move_down(&tested_tetromino);

    return can_be_placed(grid, tested_tetromino);
}

int can_move_left(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
    Tetromino_t tested_tetromino = tetromino;
    move_left(&tested_tetromino);

    return can_be_placed(grid, tested_tetromino);
}

int can_move_right(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
    Tetromino_t tested_tetromino = tetromino;
    move_right(&tested_tetromino);

    return can_be_placed(grid, tested_tetromino);
}

void remove_full_lines(Block grid[][VERTICAL_BLOCK_NB], int * score)
{
    int factor = 0;
    for (int line_number = 0; line_number < VERTICAL_BLOCK_NB; line_number++)
    {
        if (is_line_full(grid, line_number))
        {
            remove_line(grid, line_number);
            factor++;
        }
    }

    cleared_lines += factor;

    if (factor > 0)
        *score = *score + line_factors[factor]*(1 + level);

    level = cleared_lines/LINES_PER_LEVEL;
}

int is_line_full(Block grid[][VERTICAL_BLOCK_NB], int line_number)
{
    for (int x = 0; x < HORIZONTAL_BLOCK_NB; x++)
    {
        if (grid[x][line_number] == EMPTY)
            return 0;
    }

    return 1;
}

void remove_line(Block grid[][VERTICAL_BLOCK_NB], int line_number)
{
    for (int y = line_number; y >= 0; y--)
    {
        for (int x = 0; x < HORIZONTAL_BLOCK_NB; x++)
        {
            if (y == 0)
                grid[x][0] = EMPTY;
            else
                grid[x][y] = grid[x][y - 1];
        }
    }
}

int can_rotate_clockwise(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
    Tetromino_t tested_tetromino = tetromino;

    if (is_square(tetromino))
        return 0;

    rotate_clockwise(&tested_tetromino);

    return can_be_placed(grid, tested_tetromino);
}

int can_rotate_counter_clockwise(Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino)
{
    Tetromino_t tested_tetromino = tetromino;

    if (is_square(tetromino))
        return 0;

    rotate_counter_clockwise(&tested_tetromino);

    return can_be_placed(grid, tested_tetromino);
}
