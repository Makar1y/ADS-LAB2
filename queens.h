#ifndef QUEENS_H
#define QUEENS_H

#define QUEENS_NUM 5
#define PIECE_SYMBOL "♛"

/// @brief Structure to store the results of the search
typedef struct
{
    int desk_size;                  // Size of the game board
    long duration;                  // Execution time in milliseconds
    int (*results)[QUEENS_NUM][2];  // Array of found solutions
    int how_solutions;              // Total count of solutions found
    int return_code;                // Result status code
    double progress;                // Search progress (0.0 to 1.0)
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

/// @brief Finds queen positions that cover (dominate) the entire board
/// @param desk_size The dimension of the square board
/// @param timeout Maximum execution time in milliseconds (0 for no limit)
/// @param is_full_search If true (1), find all solutions; if false (0), stop after first
/// @return Pointer to Results structure, or NULL on failure
Results *find_queens(int desk_size, long timeout, int is_full_search);

/// @brief Outputs the search results to the console
/// @param results Pointer to the Results structure to print
/// @param output_format 0 for console (CMD), 1 for HTML file
/// @return SUCCESS_CODE (100) if printed, otherwise an error code
int print_results(Results *results, int output_format);

#endif