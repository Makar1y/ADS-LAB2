#ifndef QUEENS_H

enum {
    False=0, True=1, 
    TIMEOUT_CODE, SUCCESS_CODE
};

Results **find_queens(int desk_size, int timeout, int is_full_search);

#endif