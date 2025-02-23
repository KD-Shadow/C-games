#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define board_size 3
#define X 'X'
#define O 'O'

typedef struct {
  int player1;
  int player2;
  int draw;
} Score;

Score score = {.player1 = 0, .player2 = 0, .draw = 0};

void clear_screen();
void print_board(char board[board_size][board_size]);
int win_check(char board[board_size][board_size], char player);
int draw_check(char board[board_size][board_size]);
void play_game();
void player_move(char board[board_size][board_size], char player);
int validity(char board[board_size][board_size], int row, int col);

int main() {
  srand(time(NULL));
  int choice;
  do {
    play_game();
    printf("Do you want to play again? (1 for yes, 0 for no): ");
    scanf("%d", &choice);
  } while (choice == 1);
  printf("Thanks for Playing -_-\n");
}

void play_game() {
  char board[board_size][board_size] = {
      {' ', ' ', ' '},
      {' ', ' ', ' '},
      {' ', ' ', ' '},
  };

  char current_player = X;
  print_board(board);
  while (1) {
    player_move(board, current_player);
    print_board(board);
    if (win_check(board, current_player)) {
      if (current_player == X) {
        score.player1++;
        printf("Player X Won!\n");
      } else {
        score.player2++;
        printf("Player O Won!\n");
      }
      break;
    }
    if (draw_check(board)) {
      score.draw++;
      printf("It's a Draw!\n");
      break;
    }
    current_player = (current_player == X) ? O : X;
  }
}

int validity(char board[board_size][board_size], int row, int col) {
  return !(row < 0 || col < 0 || row > 2 || col > 2 || board[row][col] != ' ');
}

void player_move(char board[board_size][board_size], char player) {
  int row, col;
  do {
    printf("\nPlayer %c's turn", player);
    printf("\nEnter row and column(1-3) for %c: ", player);
    scanf("%d%d", &row, &col);
    row--; // converting to zero based
    col--; // converting to zero based
  } while (!validity(board, row, col));

  board[row][col] = player;
}

int win_check(char board[board_size][board_size], char player) {
  for (int i = 0; i < board_size; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
      return 1;
    }
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
      return 1;
    }
  }
  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
      (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
    return 1;
  }
  return 0;
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
  printf("Score: Player X: %d, Player O: %d, Draw: %d", score.player1, score.player2, score.draw);
  printf("\nTic-Tac-Toe\n");
  for (int i = 0; i < board_size; i++) {
    printf("\n");
    for (int j = 0; j < board_size; j++) {
      printf(" %c ", board[i][j]);
      if (j < board_size - 1) {
        printf("|");
      }
    }
    if (i < board_size - 1) {
      printf("\n---+---+---");
    }
  }
  printf("\n\n");
}

void clear_screen() {
#ifdef _Win32
  system("cls");
#else
  system("clear");
#endif
}

