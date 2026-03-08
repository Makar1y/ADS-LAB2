#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "utils.h"
#include "queens.h"

#define QUEENS_NUM 5

typedef struct {
    int row, col;
} Cell;

typedef struct {
    int **desk;
    int desk_size;
    int start_time;
    int timeout;
    int is_full_search;

    int ***results;
    int cur_solution;
    int cur_level;
    int ended;
} Search;

typedef struct {
    int duration;
    int ***results;
    int result_code;
    int how_solutions;
} Results;


int is_controlled(int **desk, int desk_size, int row, int col)
{
    desk[row][col] = placed;

    for (int i = 0; i < desk_size; ++i)
    {
        if (desk[i][col] == placed || desk[row][i] == placed)
        {
            return True;
        }
    }

    int max_coord = row > col ? row : col;
    Cell dig1 = {row - max_coord, col - max_coord};
    Cell dig2 = {0, row + col};

    while (dig1.col + dig1.row + dig2.row + dig2.col < desk_size * 4 ) {
        if (dig1.row < desk_size && dig1.col < desk_size) {
            if (desk[dig1.row][dig1.col] == placed)
            {
                return True;
            }
            ++dig1.row;
            ++dig1.col;
        }
        if (dig2.row < desk_size && dig2.col < desk_size) {
            if (desk[dig2.row][dig2.col] == placed)
            {
                return True;
            }
            --dig1.row;
            ++dig1.col;
        }
    }

    return 0;
}


Results **find_queens(int desk_size, int timeout, int is_full_search)
{
    Search search;
    int result_code;
    int end_time;

    search.desk = calloc(desk_size * desk_size, sizeof(int));
    search.desk_size = desk_size;
    search.results = calloc(QUEENS_NUM, 2 * sizeof(int));

    search.timeout = timeout ? timeout : -1;
    search.start_time = time(0);
    search.is_full_search = is_full_search;

    result_code = find(&search);
    end_time = time(0);

    Results *results_data = malloc(sizeof(Results));

    results_data->duration = end_time - search.start_time;
    results_data->result_code = result_code;
    results_data->results = search.results;
    results_data->how_solutions = search.cur_solution;

    free(search.desk);

    return results_data;
}

int find(Search *search)
{
    #ifdef DEBUG
        assert(desk);
    #endif

    if (search->ended) {
        return SUCCESS_CODE;
    }

    search->results[search->cur_solution][search->cur_level][0] = -1;
    search->results[search->cur_solution][search->cur_level][1] = -1;

    if (search->timeout < 0 || time(0) - search->start_time <= search->timeout)
    {
        for (int i = 0; i < search->desk_size; ++i) {
            for (int j = 0; j < search->desk_size; ++j) {
                if (!is_controlled(search->desk, search->desk_size, i, j)) 
                {
                    search->desk[i][j] = 1;
                    search->results[search->cur_solution][search->cur_level][0] = i;
                    search->results[search->cur_solution][search->cur_level][1] = j;

                    if(search->cur_level = QUEENS_NUM - 1)
                    {
                        if (!search->is_full_search)
                        {
                            search->ended = 1;
                            ++search->cur_solution;
                            return SUCCESS_CODE;
                        } else {
                            realloc(search->results, (search->cur_solution + 2) * QUEENS_NUM * 2 * sizeof(int));
                            memcpy(search->results[search->cur_solution + 1], search->results[search->cur_solution], QUEENS_NUM * 2 * sizeof(int));

                            ++search->cur_solution;
                            continue;
                        }
                    } else
                    {
                        ++search->cur_level;
                        find(search);
                    }
                }
            }
        }

        if (search->cur_level == 0) {
            return SUCCESS_CODE;
        }

        --search->cur_level;
        find(search);
    }
    return TIMEOUT_CODE;
}

void print_results(Results *results) {
    
}