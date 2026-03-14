#ifndef QUEENS_UTILS_H
#define QUEENS_UTILS_H

/// @brief Size of buffer used for reading html template. Change if using custom large template.
#define BUFFER_SIZE 500

/// @brief Piece that will be shown in html output.
#define PIECE "♛" // ♜ ♞ ♝ ♛ ♚

/// @brief Prints results in html format for using with `> filename.html`.
/// @param results Array of results where each result is array of pieces where each piece is array with x and y `[NUM_OF_RESULTS][NUM_OF_PIECES][2]`.
/// @param num_of_results How results have results array
/// @param num_of_pieces How pieces in one result (each result should have exact the same num of pieces).
/// @param desk_size Desk dimension, standard is 8 (8x8).
/// @param duration Duration of algorithm that will be displayed
/// @param timedout Is algorithm timedout.
/// @param progress If algorithm timedout, how % it researched.
void results_to_html(int ***results, int num_of_results, int num_of_pieces, int desk_size, long duration, int timedout, double progress);

/// @brief Prints results in simple format for output in `console` or `.txt`.
/// @param results Array of results where each result is array of pieces where each piece is array with x and y `[NUM_OF_RESULTS][NUM_OF_PIECES][2]`.
/// @param num_of_results How results have results array
/// @param num_of_pieces How pieces in one result (each result should have exact the same num of pieces).
/// @param duration Duration of algorithm that will be displayed
/// @param timedout Is algorithm timedout.
/// @param progress If algorithm timedout, how % it researched.
void results_to_cmd(int ***results, int num_of_results, int num_of_pieces, long duration, int timedout, double progress);

#endif