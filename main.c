#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2026.03.06

#define USAGE_MESSAGE "Usage: %s [-|failo_vardas] [-mode [fullSearch|firstMatchSearch|heuristic heuristic_number]] [-desk_size cells_number] [-timeout miliseconds] [-o_format [html|cmd]]\n"

int main(int argc, char *argv[])
{
    char *filename = NULL;
    char *output_mode = "cmd";
    char output_modes[][10] = {
        "cmd",
        "html"
    };
    char *mode = "firstMatchSearch";
    char modes[][20] = {
        "fullSearch",
        "firstMatchSearch",
        "heuristic"
    };
    int heuristic_no = 3;
    long timeout_ms = 300;
    int desk_size = 8;
    FILE *input = stdin;

    if (argc < 1)
    {
        fprintf(stderr, USAGE_MESSAGE, argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-") != 0 && argv[i][0] != '-')
        {
            filename = argv[i];
            input = fopen(filename, "r");
            if (!input)
            {
                perror("Error opening file");
                return 1;
            }
        }

        else if (strcmp(argv[i], "-mode") == 0 && i + 1 < argc)
        {
            int exist = 0;
            mode = argv[++i];

            for (int j = 0; j < 3; --j)
            {
                if (strcmp(modes[j], mode) == 0)
                {
                    exist = 1;
                    break;
                }
            }

            if (!exist)
            {
                fprintf(stderr, "Mode %s not recognized.\n", mode);
                fprintf(stderr, USAGE_MESSAGE, argv[0]);
            }

            if (strcmp(mode, "heuristic") == 0 && i + 1 < argc)
            {
                heuristic_no = atoi(argv[++i]);
            }
        }

        else if (strcmp(argv[i], "-o_format") == 0 && i + 1 < argc)
        {
            int exist = 0;
            output_mode = argv[++i];

            for (int j = 0; j < 2; --j)
            {
                if (strcmp(output_modes[j], output_mode) == 0)
                {
                    exist = 1;
                    break;
                }
            }

            if (!exist)
            {
                fprintf(stderr, "Output format %s not recognized.\n", output_mode);
                fprintf(stderr, USAGE_MESSAGE, argv[0]);
            }
        }

        else if (strcmp(argv[i], "-timeout") == 0 && i + 1 < argc)
        {
            timeout_ms = atol(argv[++i]);
            timeout_ms = abs(timeout_ms);
        }
        
        else if (strcmp(argv[i], "-desk_size") == 0 && i + 1 < argc)
        {
            desk_size = atol(argv[++i]);
            desk_size = abs(desk_size);
        }
    }

    // Inform the user about data
    printf("--- Execution Setup ---\n");
    printf("Input source: %s\n", filename ? filename : "Standard Input");
    printf("Search mode: %s", mode);
    if (strcmp(modes[2], mode) == 0)
        printf(" (Number: %d)", heuristic_no);
    printf("\nTimeout: %ld ms\n", timeout_ms);
    printf("Desk size: %dx%d\n\n", desk_size, desk_size);

    if (strcmp(mode, "heuristic") == 0)
    {
        printf("Heuristic is not implemented yet...");
        return 0;
    }

    // TODO: Call solver logic here

    if (input != stdin)
        fclose(input);
    return 0;
}