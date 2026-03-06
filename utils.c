#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 500


void results_to_html(int **results, int size) {
    if (!results) {
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
    while (fgets(buffer, BUFFER_SIZE, head)) {
        printf("%s\n", buffer);
    }

    printf("<div class=\"results-count\">Found results: <strong id=\"resultCount\">%d</strong></div>", size);

    printf("<div class=\"results-container\">");

    for (int i = 0; i < size; ++i) {
        printf("<div class=\"result-card\"><div class=\"chessboard\">");

        // TODO
        
        printf("</div></div>");
    }
    
    printf("</div></body></html>");
}