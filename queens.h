#ifndef QUEENS_H
#define QUEENS_H

#define QUEENS_NUM 5

// file/std input format: [desk_size] [mode(0|1|2)] [of(0|1)] [timeout_ms]

typedef struct {
    int desk_size;
    long duration;
    int (*results)[QUEENS_NUM][2];
    int how_solutions;
    int return_code;
    double progress;
} Results;

enum {
    False=0, True=1,
    SUCCESS_CODE = 100, TIMEOUT_CODE, INVALID_INPUT, RUNTIME_ERROR
};

Results *find_queens(int desk_size, long timeout, int is_full_search);

int print_results(Results *results, int output_format);

#endif