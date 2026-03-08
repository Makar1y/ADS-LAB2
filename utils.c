#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 500

void results_to_html(int ***results, int num_of_results, int desk_size)
{
    if (!results)
    {
#ifdef DEBUG
        assert(results);
#endif
        return;
    }
    char buffer[500];

    FILE *head = fopen("templates/head.html", "r");
#ifdef DEBUG
    assert(head);
#endif
    while (fgets(buffer, BUFFER_SIZE, head))
    {
        printf("%s\n", buffer);
    }

    printf("<div class=\"results-count\">Found results: <strong id=\"resultCount\">%d</strong></div>", num_of_results);

    printf("<div class=\"results-container\">");

    for (int r = 0; r < num_of_results; ++r)
    {
        int **desk = calloc(desk_size, desk_size * sizeof(int));
        for (int i = 0; i < num_of_results; ++i) {
            desk[results[r][i][0]][results[r][i][1]] = 1;
        }

        printf("<div class=\"result-card\"><div class=\"chessboard\">");

        for (int i = 0; i < desk_size; ++i)
        {
            for (int j = 0; j < desk_size; ++j)
            {
                // <div class="cell white">♛</div>
                printf("<div class=\"cell %s\">%s</div>",
                        i + j % 2 ? "white" : "black",
                        desk[i][j] ? "♛" : "");

            }
        }

        printf("</div></div>");
    }

    printf("</div></body></html>");
}