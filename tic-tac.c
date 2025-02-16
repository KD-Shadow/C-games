#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define board_size 3
#define X 'X'
#define O 'O'

int difficulty;
typedef struct {
    int player;
    int computer;
    int draw;
} Score;

Score score = {.player = 0, .computer = 0, .draw = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[board_size][board_size]);
int win_check(char board[board_size][board_size], char player);
int draw_check(char board[board_size][board_size]);
void play_game();
void player_move(char board[board_size][board_size]);
void computer_move(char board[board_size][board_size]);
int validity(char board[board_size][board_size], int row, int col);

int main() {
    srand(time(NULL));
    int choice;
    input_difficulty();
    do {
        play_game();
        printf("Do you want to play again? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
    } while (choice == 1);
    printf("Thanks for Playing!\n");
    printf("\nMade by Kushal Dhungana.\n");
}

void play_game() {
    char board[board_size][board_size] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char current_player = (rand() % 2 == 0) ? X : O;
    print_board(board);
    while (1) {
        if (current_player == X) {
            player_move(board);
            if (win_check(board, X)) {
                score.player++;
                print_board(board);
                printf("Congrats! You Won!\n");
                break;
            }
            current_player = O;
        } else {
            computer_move(board);
            if (win_check(board, O)) {
                score.computer++;
                print_board(board);
                printf("I Won! Try Again!\n");
                break;
            }
            current_player = X;
        }
        print_board(board);
        if (draw_check(board)) {
            score.draw++;
            printf("It's a Draw!\n");
            break;
        }
    }
}

int validity(char board[board_size][board_size], int row, int col) {
    return (row >= 0 && row < board_size && col >= 0 && col < board_size && board[row][col] == ' ');
}

void player_move(char board[board_size][board_size]) {
    int row, col;
    do {
        printf("\nPlayer X's turn\nEnter row and column (1-3) for X: ");
        while (scanf("%d%d", &row, &col) != 2) {
            printf("Invalid input! Please enter two numbers (1-3): ");
            while (getchar() != '\n');
        }
        row--;
        col--;
    } while (!validity(board, row, col));
    board[row][col] = X;
}

void computer_move(char board[board_size][board_size]) {
    // Play for win
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = O;
                if (win_check(board, O)) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }
    // Immediate block
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = X;
                if (win_check(board, X)) {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }
    // Hard mode strategy
    if (difficulty == 2) {
        if (board[1][1] == ' ') {
            board[1][1] = O;
            return;
        }
        int corner[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
        for (int i = 0; i < 4; i++) {
            if (board[corner[i][0]][corner[i][1]] == ' ') {
                board[corner[i][0]][corner[i][1]] = O;
                return;
            }
        }
    }
    // First available move
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = O;
                return;
            }
        }
    }
}

int win_check(char board[board_size][board_size], char player) {
    for (int i = 0; i < board_size; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }
    return ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player));
}

int draw_check(char board[board_size][board_size]) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void print_board(char board[board_size][board_size]) {
    clear_screen();
    printf("\nScore: Player X: %d, Computer: %d, Draw: %d\n\n", score.player, score.computer, score.draw);
    printf("    1   2   3\n");
    printf("  -------------\n");
    for (int i = 0; i < board_size; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < board_size; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n  -------------\n");
    }
    printf("\n");
}

void input_difficulty() {
    do {
        printf("Select Difficulty Level:\n1. Standard\n2. Hard Mode\nEnter your choice: ");
        scanf("%d", &difficulty);
    } while (difficulty != 1 && difficulty != 2);
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

