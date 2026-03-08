#ifndef QUEENS_H
#define QUEENS_H

typedef struct {
    int desk_size;
    int duration;
    int ***results;
    int how_solutions;
} Results;

enum {
    False=0, True=1,
    SUCCESS_CODE = 100, TIMEOUT_CODE, INVALID_INPUT, RUNTIME_ERROR
};

Results *find_queens(int desk_size, int timeout, int is_full_search);

int print_results(Results *results, int output_format);

#endif