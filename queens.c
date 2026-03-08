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
    int return_code;
} Search;

void find(Search*);


int is_controlled(int **desk, int desk_size, int row, int col)
{
    for (int i = 0; i < desk_size; ++i)
    {
        if (desk[i][col] || desk[row][i])
        {
            return True;
        }
    }

    int max_coord = row > col ? row : col;
    Cell dig1 = {row - max_coord, col - max_coord};
    Cell dig2 = {0, row + col};

    while (dig1.col + dig1.row + dig2.row + dig2.col < desk_size * 4 ) {
        if (dig1.row < desk_size && dig1.col < desk_size) {
            if (desk[dig1.row][dig1.col])
            {
                return True;
            }
            ++dig1.row;
            ++dig1.col;
        }
        if (dig2.row < desk_size && dig2.col < desk_size) {
            if (desk[dig2.row][dig2.col])
            {
                return True;
            }
            --dig1.row;
            ++dig1.col;
        }
    }

    return 0;
}


Results *find_queens(int desk_size, int timeout, int is_full_search)
{
    if (desk_size <= 0)
    {
        return NULL;
    }
    Search search;
    int result_code;
    int end_time;

    search.desk = calloc(desk_size * desk_size, sizeof(int));
    search.desk_size = desk_size;
    search.results = calloc(QUEENS_NUM, 2 * sizeof(int));
    search.is_full_search = is_full_search;
    search.return_code = SUCCESS_CODE;

    search.timeout = timeout ? timeout : -1;
    search.start_time = time(0);

    find(&search);
    end_time = time(0);

    result_code = search.return_code;

    if (result_code == TIMEOUT_CODE)
    {
        printf("Timeout reached...\n\n");
    }
    else if (result_code == RUNTIME_ERROR)
    {
        printf("Error occurred while finding solutions...\n\n");
        free(search.desk);
        free(search.results);
        return NULL;
    }

    Results *results_data = malloc(sizeof(Results));

    results_data->duration = end_time - search.start_time;
    results_data->results = search.results;
    results_data->how_solutions = search.cur_solution;
    results_data->desk_size = desk_size;

    free(search.desk);

    return results_data;
}

void find(Search *search)
{
    #ifdef DEBUG
        assert(desk);
    #endif

    if (search->ended) {
        return;
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
                            return;
                        } else {
                            search->results = realloc(search->results, (search->cur_solution + 2) * QUEENS_NUM * 2 * sizeof(int));
                            if (!search->results) {
                                search->return_code = RUNTIME_ERROR;
                                search->ended = 1;
                                return;
                            }

                            memcpy(search->results[search->cur_solution + 1], search->results[search->cur_solution], QUEENS_NUM * 2 * sizeof(int));

                            search->desk[i][j] = 0;
                            ++search->cur_solution;
                            continue;
                        }
                    } else
                    {
                        ++search->cur_level;
                        find(search);
                        search->desk[i][j] = 0;
                    }
                }
            }
        }

        if (search->cur_level == 0) {
            return;
        }

        --search->cur_level;
        find(search);
    }
    search->ended = 1;
    search->return_code = TIMEOUT_CODE;
    return;
}

int print_results(Results *results, int output_format) {
    if (!results) {
        return INVALID_INPUT;
    }

    printf("Search duration: %s ms\n", results->duration);

    if (output_format) {
        results_to_html(results->results, results->how_solutions, QUEENS_NUM, results->desk_size);
    } else {
        results_to_cmd(results->results, results->how_solutions, QUEENS_NUM);
    }
    return SUCCESS_CODE;
}