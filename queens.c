#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

// States
enum
{
    clear,
    placed,
    controlled
};

typedef struct {
    int row, col;
} Cell;

void place_queen(int **desk, int size, int row, int col)
{
    desk[row][col] = placed;

    for (int i = 0; i < size; ++i)
    {
        if (desk[i][col] == clear)
        {
            desk[i][col] = controlled;
        }
        if (desk[row][i] == clear)
        {
            desk[row][i] = controlled;
        }
    }

    int max_coord = row > col ? row : col;
    Cell dig1 = {row - max_coord, col - max_coord};
    Cell dig2 = {0, row + col};

    while (dig1.col + dig1.row + dig2.row + dig2.col < size * 4 ) {
        if (dig1.row < size && dig1.col < size) {
            if (desk[dig1.row][dig1.col] == clear)
            {
                desk[dig1.row][dig1.col] = controlled;
            }
            ++dig1.row;
            ++dig1.col;
        }
        if (dig2.row < size && dig2.col < size) {
            if (desk[dig2.row][dig2.col] == clear)
            {
                desk[dig2.row][dig2.col] = controlled;
            }
            --dig1.row;
            ++dig1.col;
        }
    }
}

void delete_queen(int **desk, int size, int row, int col)
{
}

int **find_queens(int size, int _timeout, int full_search)
{
    time_t start = time(0);
    int **desk = calloc(size * size, sizeof(int));
    int timeout = _timeout ? _timeout : -1;

    while (timeout < 0 || time(0) - timeout <= start)
    {
    }
}