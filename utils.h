#ifndef QUEENS_UTILS_H
#define QUEENS_UTILS_H

#define BUFFER_SIZE 500
#define NUM_OF_PIECES 5
#define PIECE "♛" // ♜ ♞ ♝ ♛ ♚


void results_to_html(int (*results)[NUM_OF_PIECES][2], int num_of_results, int num_of_pieces, int desk_size, long duration);

void results_to_cmd(int (*results)[NUM_OF_PIECES][2], int num_of_results, int num_of_pieces, long duration);


#endif