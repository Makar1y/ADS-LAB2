#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

void results_to_html(int (*results)[NUM_OF_PIECES][2], int num_of_results, int num_of_pieces, int desk_size, long duration)
{
    if (!results)
    {
        return;
    }
    char buffer[BUFFER_SIZE];

    FILE *head = fopen("templates/head.html", "r");
    if (head == NULL) {
        fprintf(stderr, "Error opening template for html output.\n");
        return;
    }
    while (fgets(buffer, BUFFER_SIZE, head))
    {
        printf("%s", buffer);
    }
    fclose(head);

    printf("<div class=\"stats\">\n");
    printf("\t<div>Solutions Found: <strong>%d</strong></div>\n", num_of_results);
    printf("\t<div style=\"color: var(--text-secondary); font-size: 0.9rem; margin-top: 0.5rem;\">Search Duration: %ld ms</div>\n", duration, desk_size, desk_size);
    printf("</div>\n");

    if (num_of_results == 0) {
        printf("<div class=\"no-results\">No solutions found for this configuration.</div>\n");
    } else {
        printf("<div class=\"results-container\">\n");

        for (int r = 0; r < num_of_results; ++r)
        {
            int *desk = (int *)calloc(desk_size * desk_size, sizeof(int));
            if (!desk) {
                fprintf(stderr, "Memory allocation failed in results_to_html\n");
                return;
            }

            for (int i = 0; i < num_of_pieces; ++i) {
                int row = results[r][i][0];
                int col = results[r][i][1];
                if (row >= 0 && row < desk_size && col >= 0 && col < desk_size) {
                    desk[row * desk_size + col] = 1;
                }
            }

            printf("<div class=\"result-card\">\n");
            printf("\t<div class=\"result-header\">Solution #%d</div>\n", r + 1);
            printf("\t<div class=\"chessboard\" style=\"grid-template-columns: repeat(%d, 35px); grid-template-rows: repeat(%d, 35px);\">\n", desk_size, desk_size);

            for (int i = 0; i < desk_size; ++i)
            {
                for (int j = 0; j < desk_size; ++j)
                {
                    int is_piece = desk[i * desk_size + j];
                    printf("\t\t<div class=\"cell %s %s\">%s</div>\n",
                            (i + j) % 2 ? "white" : "black",
                            is_piece ? "has-piece" : "",
                            is_piece ? PIECE : "");
                }
            }

            printf("\t</div>\n");
            printf("</div>\n");
            free(desk);
        }
        printf("</div>\n");
    }

    printf("</body></html>\n");
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