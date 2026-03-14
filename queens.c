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
    int desk_size;
    clock_t start_time;
    long timeout;
    int is_full_search;
    int (*results)[QUEENS_NUM][2];
    int cur_solution;
    int cur_level;
    int ended;
    int return_code;
    double progress;
} Search;

void find_domination(Search *, int, int, double);

int is_board_covered(Search *search)
{
    int size = search->desk_size;
    for (int r = 0; r < size; ++r)
    {
        for (int c = 0; c < size; ++c)
        {
            int covered = 0;
            for (int q = 0; q < QUEENS_NUM; ++q)
            {
                int qr = search->results[search->cur_solution][q][0];
                int qc = search->results[search->cur_solution][q][1];

                if (qr == r || qc == c || abs(qr - r) == abs(qc - c))
                {
                    covered = 1;
                    break;
                }
            }
            if (!covered)
            {
                return 0;
            }
        }
    }
    return 1;
}

Results *find_queens(int desk_size, long timeout, int is_full_search)
{
    if (desk_size <= 0)
    {
        fprintf(stderr, "Error, desk size must be positive integer...\n");
        return NULL;
    }
    Search search = {0};
    int result_code;
    clock_t end_time;

    search.desk_size = desk_size;

    search.results = malloc(sizeof(int[QUEENS_NUM][2]) * 2);

    search.is_full_search = is_full_search;
    search.return_code = SUCCESS_CODE;

    if (!search.results)
    {
        fprintf(stderr, "Error allocating memory...\n");
        return NULL;
    }

    search.timeout = timeout;
    search.start_time = clock();

    DEBUG_PRINT("Starting search...");

    find_domination(&search, 0, 0, 1.0);
    end_time = clock();

    DEBUG_PRINT("Search ended with %d results and %d return code.", search.cur_solution, search.return_code);

    if (search.return_code == RUNTIME_ERROR)
    {
        fprintf(stderr, "Error occurred while finding solutions...\n\n");

        free(search.results);
        return NULL;
    }

    Results *results_data = malloc(sizeof(Results));

    results_data->duration = ((double)(end_time - search.start_time) / CLOCKS_PER_SEC) * 1000;
    results_data->results = search.results;
    results_data->how_solutions = search.cur_solution;
    results_data->desk_size = desk_size;
    results_data->return_code = search.return_code;
    results_data->progress = search.progress;

    return results_data;
}

void find_domination(Search *search, int start_index, int queens_placed, double weight)
{
    // Returning
    if (search->ended)
    {
        return;
    }
    if (search->timeout > 0)
    {
        clock_t current_time = clock();
        double elapsed_ms = ((double)(current_time - search->start_time) / CLOCKS_PER_SEC) * 1000;

        if (elapsed_ms > search->timeout)
        {
            search->return_code = TIMEOUT_CODE;
            search->ended = 1;
            return;
        }
    }

    // Save
    if (queens_placed == QUEENS_NUM)
    {
        if (is_board_covered(search))
        {
            ++search->cur_solution;

            if (!search->is_full_search)
            {
                search->ended = 1;
            }
            else
            {
                void *tmp = realloc(search->results, sizeof(int[QUEENS_NUM][2]) * (search->cur_solution + 1));
                if (!tmp)
                {
                    search->return_code = RUNTIME_ERROR;
                    search->ended = 1;
                    return;
                }
                search->results = tmp;
                memcpy(search->results[search->cur_solution],
                       search->results[search->cur_solution - 1],
                       sizeof(int[QUEENS_NUM][2]));
            }
        }
        return;
    }

    // Main search
    int total_cells = search->desk_size * search->desk_size;
    int end_index = total_cells - (QUEENS_NUM - queens_placed);
    int count = end_index - start_index;

    for (int i = start_index; i < end_index; ++i)
    {
        int r = i / search->desk_size;
        int c = i % search->desk_size;

        search->results[search->cur_solution][queens_placed][0] = r;
        search->results[search->cur_solution][queens_placed][1] = c;

        find_domination(search, i + 1, queens_placed + 1, weight / count);

        if (search->ended)
        {
            return;
        }

        search->progress += weight / count;
    }
}

int print_results(Results *results, int output_format)
{
    if (!results)
    {
        fprintf(stderr, "Error(print results), NULL struct given...\n");
        return INVALID_INPUT;
    }

    if (output_format)
    {
        results_to_html(results->results, results->how_solutions, QUEENS_NUM, results->desk_size, results->duration, results->return_code == TIMEOUT_CODE, results->progress * 100.0, PIECE_SYMBOL);
    }
    else
    {
        results_to_cmd(results->results, results->how_solutions, QUEENS_NUM, results->duration, results->return_code == TIMEOUT_CODE, results->progress * 100.0);
    }
    return SUCCESS_CODE;
}