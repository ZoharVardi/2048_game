
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"
#define VALID_OPTIONS "nrlude"

char valid_input() {
    while (1) {
        // Read single char and clear buffer
        char ch = getchar();
        ch = tolower(ch);
        while (getchar() != '\n'); // Clear input buffer

        if (valid_option(ch)) {
            return ch;
        }
        else {
            printf("Wrong option\n");
            display_manu();
        }
    }
}


int valid_option(char ch)
{
    const char* ptr = VALID_OPTIONS;
    while (*ptr != '\0') {
        if (ch == *ptr) {
            return 1;
        }
        ptr++;
    }

    return 0;
}





