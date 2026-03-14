#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queens.h"
#include "DEBUG.H"

// 2026.03.06

#define USAGE_MESSAGE "Usage: %s [-|failo_vardas] [-mode [fullSearch|firstMatchSearch|heuristic heuristic_number]] [-desk_size cells_number] [-timeout miliseconds] [-of [html|cmd]]\n"
#define FILE_INPUT_USAGE "file/std input format: [desk_size] [mode(0|1|2)] [of(0|1)] [timeout_ms]"

int main(int argc, char *argv[])
{
    char *filename = NULL;
    int output_mode = 0;
    char output_modes[2][10] = {
        "cmd",
        "html"};
    int mode = 0;
    char modes[3][20] = {
        "firstMatchSearch",
        "fullSearch",
        "heuristic"};
    int heuristic_no = 3;
    long timeout_ms = 0;
    int desk_size = 8;
    FILE *input = stdin;

    if (argc <= 1)
    {
        fprintf(stderr, USAGE_MESSAGE, argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-mode") == 0 && i + 1 < argc)
            {
                int exist = 0;
                char *tmp = argv[++i];

                for (int j = 0; j < 3; ++j)
                {
                    if (strcmp(modes[j], tmp) == 0)
                    {
                        exist = 1;
                        mode = j;
                        break;
                    }
                }

                if (!exist)
                {
                    fprintf(stderr, "Mode %s not recognized.\n", tmp);
                    fprintf(stderr, USAGE_MESSAGE, argv[0]);
                    exit(1);
                }

                if (strcmp(tmp, "heuristic") == 0 && i + 1 < argc)
                {
                    heuristic_no = atoi(argv[++i]);
                }
            }

            else if (strcmp(argv[i], "-of") == 0 && i + 1 < argc)
            {
                int exist = 0;
                char *tmp = argv[++i];

                for (int j = 0; j < 2; ++j)
                {
                    if (strcmp(output_modes[j], tmp) == 0)
                    {
                        output_mode = j;
                        exist = 1;
                        break;
                    }
                }

                if (!exist)
                {
                    fprintf(stderr, "Output format %s not recognized.\n", tmp);
                    fprintf(stderr, USAGE_MESSAGE, argv[0]);
                    exit(1);
                }
            }

            else if (strcmp(argv[i], "-timeout") == 0 && i + 1 < argc)
            {
                timeout_ms = atol(argv[++i]);
                timeout_ms = abs(timeout_ms);
            }

            else if (strcmp(argv[i], "-desk_size") == 0 && i + 1 < argc)
            {
                desk_size = abs(atoi(argv[++i]));
            }
            else if (strcmp(argv[i], "-") == 0)
            {
                filename = argv[i];
                if (scanf("%d %d %d %ld", &desk_size, &mode, &output_mode, &timeout_ms) != 4)
                {
                    printf("Invalid arguments count (should be 4)\n%s\n", FILE_INPUT_USAGE);
                    exit(1);
                };
            }
            else
            {
                fprintf(stderr, "Argument %s not recognized.\n", argv[i]);
                fprintf(stderr, USAGE_MESSAGE, argv[0]);
                exit(1);
            }
        }
        else
        {
            filename = argv[i];
            input = fopen(filename, "r");

            if (!input)
            {
                perror("Error opening input file");
                exit(1);
            }
            if (fscanf(input, "%d %d %d %ld", &desk_size, &mode, &output_mode, &timeout_ms) != 4)
            {
                printf("Invalid arguments count from file (should be 4)\n%s\n", FILE_INPUT_USAGE);
                exit(1);
            };
            fclose(input);
        }
    }

    // Inform the user about data
    if (output_mode == 1)
        printf("<p>");
    printf("\n--- Execution Setup ---\n");
    if (output_mode == 1)
        printf("<br>");

    printf("Input source: %s\n", filename ? (strcmp(filename, "-") == 0 ? "cmd" : filename) : "Standard Input");
    if (output_mode == 1)
        printf("<br>");

    printf("Search mode: %s", modes[mode]);
    if (mode == 2)
    {
        printf(" (Number: %d)", heuristic_no);
    }
    if (output_mode == 1)
        printf("<br>");

    printf("\nTimeout: %ld ms\n", timeout_ms);
    if (output_mode == 1)
        printf("<br>");

    printf("Desk size: %dx%d\n", desk_size, desk_size);
    if (output_mode == 1)
        printf("<br>");

    printf("Output format: %s\n\n", output_modes[output_mode]);
    if (output_mode == 1)
        printf("</p>");

    if (mode == 2)
    {
        printf("Heuristic is not implemented yet...");
        return 0;
    }

    print_results(find_queens(desk_size, timeout_ms, mode), output_mode);
    return 0;
}