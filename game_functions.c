#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "game_functions.h"

int game_started(char user_input, int game_started)
{
    if (((user_input == 'r' || user_input == 'l' || user_input == 'u' || user_input == 'd'))
        && (!game_started))
    {
        printf("need to start game first\n\n");
        return 0;
    }
    return 1;
}

void clear_board(int* board, int size) {
    for (int i = 0; i < size * size; i++) {
        *(board + i) = 0; 
    }
}

void update_max_score(int* max_score, int current_score) {
    if (current_score > *max_score) {
        *max_score = current_score; // Update best score
   }
}

void start_new_game(int* board, int size, int* current_score) {
    // Reset the board to all zeros
    clear_board(board, size);

    // Reset the score
    *current_score = 0;

    // Place two random tiles on the board
    int* empty_cell1 = generate_random_pointer(board, size);
    if (empty_cell1 != NULL) {
        *empty_cell1 = generate_random_2_or_4();
    }

    int* empty_cell2 = generate_random_pointer(board, size);
    if (empty_cell2 != NULL) {
        *empty_cell2 = generate_random_2_or_4();
    }
}

int update_board(int* board, int size, int scoreToWin, int current_score, int first_play) {
    int* empty_cell = generate_random_pointer(board, size);
    if (empty_cell) {
        *empty_cell = generate_random_2_or_4();
        return 1; // Tile successfully added
    }

    // Check if no valid moves exist
    if (!any_valid_moves((const int*)board, size)) {
        return 0; // Game ends
    }

    return 1; // Game continues
}

int* generate_random_pointer(const int* board, int size) {
    int random_index = 0;
    int first_empty_index = check_for_empty_cells(board, size);

    // Return NULL if board is full
    if (first_empty_index == -1) {
        return NULL;
    }

    // Keep trying until we find an empty cell
    do {
        random_index = first_empty_index + rand() % (size * size - first_empty_index);
    } while (!check_cell_for_0(board, random_index));

    return (int*)(board + random_index);
}

int generate_random_2_or_4() {
    // 70% chance for 2, 30% chance for 4
    float random_value = (float)rand() / RAND_MAX;
    return (random_value < TWO_CHANCE) ? 2 : 4;
}

// Returns index of first empty cell or -1 if none found
int check_for_empty_cells(const int* board, int size) {
    int current_index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            current_index = i * size + j;
            if (check_cell_for_0(board, current_index)) {
                return current_index;
            }
        }
    }
    return -1;
}

int check_cell_for_0(const int* board, int current_index) {
    if (*(board + current_index) == 0) {
        return 1;
    }

    return 0;
}


// Returns a pointer to the cell based on direction and position using pointer arithmetic
int* get_cell_ptr(int* board, int size, int primary_idx, int secondary_idx, int is_horizontal) {
    if (is_horizontal) {
        return (board + (primary_idx * size + secondary_idx));
    }
    else {
        return (board + (secondary_idx * size + primary_idx));
    }
}

// Moves all non-zero numbers to one side of the line  
void compact_numbers(int* board, int size, int line_idx, int is_horizontal, int is_positive_direction, int* changed) {
    int write_pos;
    int step;
    int read_pos;

    // Set initial positions and direction based on movement direction
    if (is_positive_direction) {
        write_pos = size - 1;
        step = -1;
        read_pos = size - 1;
    }
    else {
        write_pos = 0;
        step = 1;
        read_pos = 0;
    }

    while (1) {
        int* current = get_cell_ptr(board, size, line_idx, read_pos, is_horizontal);
        if (*current != 0) {
            int* write_cell = get_cell_ptr(board, size, line_idx, write_pos, is_horizontal);
            // Move number if its not already in position
            if (current != write_cell) {
                *write_cell = *current;
                *current = 0;
                *changed = 1;
            }
            write_pos += step;
        }
        // Check if we reached the end of the line
        if (is_positive_direction) {
            if (read_pos <= 0) {
                break;
            }
        }
        else {
            if (read_pos >= size - 1) {
                break;
            }
        }
        read_pos += step;
    }
}

// Merges equal numbers and shifts the remaining numbers
void merge_numbers(int* board, int size, int line_idx, int is_horizontal, int is_positive_direction, int* current_score, int* changed) {
    int start;
    int step;
    int merge_occurred = 0;
    int i;

    // Set initial positions and direction
    if (is_positive_direction) {
        start = size - 1;
        step = -1;
    }
    else {
        start = 0;
        step = 1;
    }

    i = start;
    while (1) {
        int* current = get_cell_ptr(board, size, line_idx, i, is_horizontal);
        int* next = get_cell_ptr(board, size, line_idx, i + step, is_horizontal);
        // Check for mergeable tiles
        if (*current != 0 && *current == *next) {
            *current *= 2;
            *current_score += *current;
            // Shift all numbers after merged position
            int j = i + step;
            while (1) {
                int* to_shift = get_cell_ptr(board, size, line_idx, j, is_horizontal);
                int* next_num = get_cell_ptr(board, size, line_idx, j + step, is_horizontal);
                *to_shift = *next_num;
                // Check if we reached the end
                if (is_positive_direction) {
                    if (j <= 0) {
                        break;
                    }
                }
                else {
                    if (j >= size - 2) {
                        break;
                    }
                }
                j += step;
            }
            // Clear the last cell after shifting
            int last_pos;
            if (is_positive_direction) {
                last_pos = 0;
            }
            else {
                last_pos = size - 1;
            }
            int* last = get_cell_ptr(board, size, line_idx, last_pos, is_horizontal);
            *last = 0;
            merge_occurred = 1;
            i += step; // Skip merged number
        }
        // Check if we processed the whole line
        if (is_positive_direction) {
            if (i <= 0) {
                break;
            }
        }
        else {
            if (i >= size - 1) {
                break;
            }
        }
        i += step;
    }
    // Update changed flag if any merges occurred
    if (merge_occurred) {
        *changed = 1;
    }
}



int process_direction(int* board, int size, int* current_score, int scoreToWin, int is_horizontal, int is_positive_direction) {
    int board_changed = 0;

    for (int i = 0; i < size; i++) {
        // First compact all numbers
        compact_numbers(board, size, i, is_horizontal, is_positive_direction, &board_changed);

        // Then do one merge pass
        merge_numbers(board, size, i, is_horizontal, is_positive_direction, current_score, &board_changed);

        // Compact again after merging
        compact_numbers(board, size, i, is_horizontal, is_positive_direction, &board_changed);
    }

    return board_changed;
}





int any_valid_moves(const int* board, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            int current = *(board + row * size + col);

            // Check for empty cell
            if (current == 0) {
                return 1; // Valid move exists
            }

            // Check right
            if (col + 1 < size && current == *(board + row * size + (col + 1))) {
                return 1; // Mergeable tiles
            }

            // Check down
            if (row + 1 < size && current == *(board + (row + 1) * size + col)) {
                return 1; // Mergeable tiles
            }
        }
    }

    return 0; // No valid moves left
}


int check_for_win(const int* board, int size, int scoreToWin) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(board + i * size + j) == scoreToWin) {
                return 1; // Winning tile found
            }
        }
    }
    return 0; // No winning tile
}
