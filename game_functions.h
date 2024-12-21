#ifndef __GAME_FUNCTIONS__
#define __GAME_FUNCTIONS__
#define TWO_CHANCE 0.7
#define FOUR_CHANCE 0.3

int game_started(char user_input, int game_started);
void clear_board(int* board, int size);
void update_max_score(int* max_score, int current_score);
void start_new_game(int* board, int size, int* current_score);
int update_board(int* board, int size, int scoreToWin, int current_score, int first_play);
int generate_random_2_or_4();
int* generate_random_pointer(const int* board, int size); 
int check_for_empty_cells(const int* board, int size); 
int check_cell_for_0(const int* board, int current_index); 
int process_direction(int* board, int size, int* current_score, int scoreToWin, int is_horizontal, int is_positive_direction);
int any_valid_moves(const int* board, int size); 
int check_for_win(const int* board, int size, int scoreToWin); 
int* get_cell_ptr(int* board, int size, int primary_idx, int secondary_idx, int is_horizontal);
void compact_numbers(int* board, int size, int line_idx, int is_horizontal, int is_positive_direction, int* changed);
void merge_numbers(int* board, int size, int line_idx, int is_horizontal, int is_positive_direction, int* current_score, int* changed);

#endif
