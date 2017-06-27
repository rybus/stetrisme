#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "constants.h"
#include "matrix.h"

Tetromino_t get_tetromino(int type_block)
{
    Tetromino_t tetromino;

    Tetromino_t tetrominos[7] =
    {
        {
            .block =
            {   {3, 3, 3, 3},
                {2, 2, 2, 2},
                {3, 3, 3, 3},
                {3, 3, 3, 3}
            }
        },

        {
            .block =
            {   {3, 2, 2, 0},
                {3, 2, 2, 0},
                {3, 3, 3, 0},
                {0, 0, 0, 0}
            }
        },

        {
            .block =
            {   {3, 2, 3, 0},
                {2, 2, 2, 0},
                {3, 3, 3, 0},
                {0, 0, 0, 0}
            }
        },

        {
            .block =
            {   {3, 3, 2, 0},
                {2, 2, 2, 0},
                {3, 3, 3, 0},
                {0, 0, 0, 0}
            }
        },

        {
            .block =
            {   {2, 3, 3, 0},
                {2, 2, 2, 0},
                {3, 3, 3, 0},
                {0, 0, 0, 0}
            }
        },

        {
            .block =
            {   {2, 2, 3, 0},
                {3, 2, 2, 0},
                {3, 3, 3, 0},
                {0, 0, 0, 0}
            }
        },

        {
            .block =
            {   {3, 2, 2, 0},
                {2, 2, 3, 0},
                {3, 3, 3, 0},
                {0, 0, 0, 0}
            }
        }
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            tetromino.block[i][j] = tetrominos[type_block].block[i][j];
    }

    tetromino.pos.x = HORIZONTAL_BLOCK_NB/2 - 3;
    tetromino.pos.y = 0;

    return tetromino;
}

void move_down(Tetromino_t* tetromino)
{
    tetromino->pos.y += 1;
}

void move_left(Tetromino_t* tetromino)
{
    tetromino->pos.x -= 1;
}

void move_right(Tetromino_t* tetromino)
{
    tetromino->pos.x += 1;
}


void rotate_clockwise(Tetromino_t* tetromino)
{
    transpose_array(tetromino->block);
    reverse_rows(tetromino->block);
}

void rotate_counter_clockwise(Tetromino_t* tetromino)
{
    transpose_array(tetromino->block);
    reverse_columns(tetromino->block);
}

int is_square(Tetromino_t tetromino)
{
    Dimension_t dimensions = get_matrix_dimensions(tetromino.block, EXCLUDE_STUFFING);

    return (dimensions.max_x - dimensions.min_x == dimensions.max_y - dimensions.min_y);
}
