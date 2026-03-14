#ifndef QUEENS_H
#define QUEENS_H

#define QUEENS_NUM 5

/// @brief Structure for comfort results storing
typedef struct
{
    int desk_size;
    long duration;
    int (*results)[QUEENS_NUM][2];
    int how_solutions;
    int return_code;
    double progress;
} Results;

/// @brief Return codes
enum
{
    False = 0,
    True = 1,
    SUCCESS_CODE = 100,
    TIMEOUT_CODE,
    INVALID_INPUT,
    RUNTIME_ERROR
};

/// @brief
/// @param desk_size
/// @param timeout
/// @param is_full_search
/// @return
Results *find_queens(int desk_size, long timeout, int is_full_search);

/// @brief
/// @param results
/// @param output_format
/// @return
int print_results(Results *results, int output_format);

#endif