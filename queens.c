#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "queens.h"
#include "DEBUG.H"

typedef struct
{
    int row, col;
} Cell;

typedef struct
{
    int **desk;
    int desk_size;
    time_t start_time;
    int timeout;
    int is_full_search;

    int (*results)[QUEENS_NUM][2];
    int cur_solution;
    int cur_level;
    int ended;
    int return_code;
} Search;

void find(Search *);

int is_controlled(int **desk, int desk_size, int row, int col)
{
    for (int i = 0; i < desk_size; ++i)
    {
        for (int j = 0; j < desk_size; ++j)
        {
            if (desk[i][j])
            {
                if (i == row || j == col) return 1;

                int delta_row = abs(i - row);
                int delta_col = abs(j - col);
                if (delta_row == delta_col) return 1;
            }
        }
    }
    return 0;
}


Results *find_queens(int desk_size, int timeout, int is_full_search)
{
    if (desk_size <= 0)
    {
        fprintf(stderr, "Error, desk size must be positive integer...\n");
        return NULL;
    }
    Search search = {0};
    int result_code;
    time_t end_time;

    search.desk_size = desk_size;
    search.desk = malloc(desk_size * sizeof(int *));
    for (int i = 0; i < desk_size; ++i)
    {
        search.desk[i] = calloc(desk_size, sizeof(int));
    }

    search.results = malloc(sizeof(int[QUEENS_NUM][2]) * 2);

    search.is_full_search = is_full_search;
    search.return_code = SUCCESS_CODE;

    if (!search.desk || !search.results)
    {
        fprintf(stderr, "Error allocating memory...\n");
        return NULL;
    }

    search.timeout = timeout ? timeout / 1000.f : -1;
    search.start_time = time(0);

    DEBUG_PRINT("Starting search...");

    find(&search);
    end_time = time(0);

    DEBUG_PRINT("Search ended with %d results", search.cur_solution);

    result_code = search.return_code;

    if (result_code == TIMEOUT_CODE)
    {
        printf("Timeout reached...\n\n");
    }
    else if (result_code == RUNTIME_ERROR)
    {
        fprintf(stderr, "Error occurred while finding solutions...\n\n");
        for (int i = 0; i < desk_size; i++)
            free(search.desk[i]);
        free(search.desk);
        free(search.results);
        return NULL;
    }

    Results *results_data = malloc(sizeof(Results));

    results_data->duration = end_time - search.start_time;
    results_data->results = search.results;
    results_data->how_solutions = search.cur_solution;
    results_data->desk_size = desk_size;

    for (int i = 0; i < desk_size; i++)
        free(search.desk[i]);
    free(search.desk);

    return results_data;
}

void find(Search *search)
{

    if (search->ended)
    {
        return;
    }

    search->results[search->cur_solution][search->cur_level][0] = -1;
    search->results[search->cur_solution][search->cur_level][1] = -1;

    if (search->timeout < 0 || time(0) - search->start_time <= search->timeout)
    {
        for (int i = 0; i < search->desk_size; ++i)
        {
            for (int j = 0; j < search->desk_size; ++j)
            {
                if (!is_controlled(search->desk, search->desk_size, i, j))
                {
                    search->desk[i][j] = 1;
                    search->results[search->cur_solution][search->cur_level][0] = i;
                    search->results[search->cur_solution][search->cur_level][1] = j;

                    if (search->cur_level == QUEENS_NUM - 1)
                    {
                        if (!search->is_full_search)
                        {
                            search->ended = 1;
                            ++search->cur_solution;
                            DEBUG_PRINT("Sarch ended with first match. level: %d, solution: %d", search->cur_level, search->cur_solution);
                            return;
                        }
                        else
                        {

                            void *tmp = realloc(search->results, sizeof(int[QUEENS_NUM][2]) * (search->cur_solution + 2));

                            if (!tmp)
                            {
                                search->return_code = RUNTIME_ERROR;
                                search->ended = 1;
                                return;
                            }

                            search->results = tmp;

                            memcpy(search->results[search->cur_solution + 1],
                                   search->results[search->cur_solution],
                                   sizeof(int[QUEENS_NUM][2]));

                            search->desk[i][j] = 0;
                            ++search->cur_solution;
                            DEBUG_PRINT("Sarch found another solution. level: %d, solution: %d", search->cur_level, search->cur_solution);
                            continue;
                        }
                    }
                    else
                    {
                        ++search->cur_level;
                        find(search);
                        if (search->ended) {
                            return;
                        }
                        search->desk[i][j] = 0;
                    }
                }
            }
        }

        if (search->cur_level == 0)
        {
            return;
        }

        --search->cur_level;
        find(search);
        if (search->ended) {
            return;
        }
    }
    search->ended = 1;
    search->return_code = TIMEOUT_CODE;
    return;
}

int print_results(Results *results, int output_format)
{
    if (!results)
    {
        fprintf(stderr, "Error(print results), NULL struct given...\n");
        return INVALID_INPUT;
    }

    printf("Search duration: %ld s\n", (long)results->duration);

    if (output_format)
    {
        results_to_html(results->results, results->how_solutions, QUEENS_NUM, results->desk_size);
    }
    else
    {
        results_to_cmd(results->results, results->how_solutions, QUEENS_NUM);
    }
    return SUCCESS_CODE;
}