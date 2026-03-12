#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

void results_to_html(int (*results)[NUM_OF_PIECES][2], int num_of_results, int num_of_pieces, int desk_size)
{
    if (!results)
    {
        return;
    }
    char buffer[500];

    FILE *head = fopen("templates/head.html", "r");
    if (head == NULL) {
        fprintf(stderr, "Error openning template for html output.\n");
        return;
    }
    while (fgets(buffer, BUFFER_SIZE, head))
    {
        printf("%s\n", buffer);
    }
    fclose(head);

    printf("<div class=\"results-count\">Found results: <strong id=\"resultCount\">%d</strong></div>\n", num_of_results);

    printf("<div class=\"results-container\">\n");

    for (int r = 0; r < num_of_results; ++r)
    {
        int desk[desk_size][desk_size];
        for(int x=0; x<desk_size; x++) 
            for(int y=0; y<desk_size; y++) desk[x][y] = 0;

        for (int i = 0; i < num_of_pieces; ++i) {
            desk[results[r][i][0]][results[r][i][1]] = 1;
        }

        printf("<div class=\"result-card\"><div class=\"chessboard\">\n");

        for (int i = 0; i < desk_size; ++i)
        {
            for (int j = 0; j < desk_size; ++j)
            {
                // <div class="cell white">♛</div>
                printf("<div class=\"cell %s\">%s</div>\n",
                        (i + j) % 2 ? "white" : "black",
                        desk[i][j] ? PIECE : "");

            }
        }

        printf("</div></div>\n");
    }

    printf("</div></body></html>\n");
}


void results_to_cmd(int (*results)[NUM_OF_PIECES][2], int num_of_results, int num_of_pieces, long duration)
{
    if (!results)
    {
        return;
    }

    printf("--- Output ---\n\n");

    printf("Search duration: %ld ms\n", duration);

    printf("Solutions found: %d\n\n", num_of_results);

    for (int r = 0; r < num_of_results; ++r)
    {
        printf("Result No. %d\n", r + 1);
        printf("[");
        for (int i = 0; i < num_of_pieces; ++i) {
            printf("%c%d,", results[r][i][0] + 97, results[r][i][1]);
        }
        printf("]\n\n");
    }
}