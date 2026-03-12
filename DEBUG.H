#ifndef DEBUG_H
#define DEBUG_H

#if defined DEBUG
#define DEBUG_PRINT(FORMAT, ...) \
            do { \
                fprintf(stderr, "\n!!! DEBUG %s - %d - %s !!! " FORMAT, __FILE_NAME__, __LINE__, __func__, ##__VA_ARGS__); \
            } while (0)
#else
#define DEBUG_PRINT(FORMAT, ...) do {} while (0)

#endif
#endif