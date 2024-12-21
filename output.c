#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "output.h"

void print_border(int border_length)
{
	for (int i = 0; i < border_length; i++)
	{
		printf("%s", BORDER);
	}
	printf("%c\n", '-');
}

void display_board(const int* board, int size) { // `board` is const since it is read-only
	for (int i = 0; i < size; i++) {
		print_border(size);
		for (int j = 0; j < size; j++) {
			printf("|");
			if (*(board + i * size + j) == 0) {
				printf("%s", EMPTY_CELL);
			}
			else {
				printf("%*d ", CELL_WIDTH, *(board + i * size + j));
			}
		}
		printf("|\n");
	}
	print_border(size);
	
}

void display_manu()
{
	printf("\n\nPlease choose one of the following options:\n");
	printf("N/n - New Game\n");
	printf("R/r - Move Right\n");
	printf("L/l - Move Left\n");
	printf("U/u - Move Up\n");
	printf("D/d - Move Down\n");
	printf("E/e - Exit\n");
}

void display_new_game(int scoreToWin)
{
	printf("------------  STARTING A GAME ------------\n");
	printf("            Highest tile for a win %d\n", scoreToWin);
	printf("------------------------------------------\n\n");
}

void display_score(int current_score, int max_score)
{
	printf("Score %d Best %d\n", current_score, max_score);
}
