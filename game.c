
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

// Name: Zohar Vardi, ID: 211466180
// Name: Anna Tsitsiashvili, ID: 322864927

void playGame(int*  board, int size, int scoreToWin) {
    char user_input = ' ';
    int max_score = 0;

    display_board(board, size);

    while (1) { // Outer loop to allow starting a new game after finishing one
        int game_active = 0, current_score = 0, first_play = 1;

        while (1) { // Inner loop: the actual game
            // Check for Game Over
            if (game_active && !any_valid_moves((const int*)board, size)) {
                printf("game over your score is %d\n", current_score);
                game_active = 0;
                break;
            }

            display_manu();
            user_input = valid_input();

            if (user_input == 'n') { // Start a new game
                display_new_game(scoreToWin);
                start_new_game(board, size, &current_score);
                first_play = 1;
                game_active = 1;
                display_score(current_score, max_score);
                display_board(board, size);
                continue;
            }

            if (user_input == 'e') { // Exit the program
                printf("Ending previous game  - your score %d best score %d\n\nBye bye\n", current_score, max_score);
                clear_board(board, size);
                return; // Exit the entire program
            }

            if (game_active) {
                int board_changed = 0;

                // Process moves
                switch (user_input) {
                case 'l': board_changed = process_direction(board, size, &current_score, scoreToWin, 1, 0); break;
                case 'r': board_changed = process_direction(board, size, &current_score,  scoreToWin, 1, 1); break;
                case 'u': board_changed = process_direction(board, size, &current_score,  scoreToWin, 0, 0); break;
                case 'd': board_changed = process_direction(board, size, &current_score,  scoreToWin, 0, 1); break;
                default:
                    continue;
                }

                if (!board_changed) { // No tiles moved
                    printf("Nothing to move in this direction, choose another option\n");
                    continue;
                }

                // Update board and check for Game Over
                if (!update_board(board, size, scoreToWin, current_score, first_play)) {
                    printf("Game over your score is %d\n", current_score);
                    game_active = 0;
                    break;
                }

                first_play = 0;
                update_max_score(&max_score, current_score);
                display_score(current_score, max_score);
                display_board(board, size);

                // Check for a winning tile AFTER displaying the board
                if (check_for_win((const int*)board, size, scoreToWin)) {
                    printf("You won %d!  - Ending Game\n", scoreToWin);
                    game_active = 0;
                    break;
                }
            }
            else {
                printf("Need to start game first\n");
            }
        }
    }
}
