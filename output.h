#ifndef __OUTPUT__
#define __OUTPUT__
#include "game.h"
#define BORDER "-------"
#define EMPTY_CELL "      "
#define CELL_WIDTH 5

void print_border(int border_length);
void display_board(const int* board, int size); // Board is const
void display_manu();
void display_new_game(int scoreToWin);
void display_score(int current_score, int max_score);

#endif
