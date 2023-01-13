#include <ctype.h>

#include <stdio.h>

#include <assert.h>

#include <string.h>

#include <stdbool.h>
 // make_move(board , column , player) updates the board following a move
// by the given player in the given column; returns false if the move
// was illegal because the column was full
// requires: 0 <= column < 7
// player is either 'X' or 'O'
bool make_move(char board[6][7], int column, char player) {
  for (int row = 5; row >= 0; row--) {
    if (!(board[row][column] == 'X' || board[row][column] == 'O')) {
      board[row][column] = player;
      return true;
    }
  }
  return false;
}
// check_win(board) returns true if the given player has 4 connected
// pieces on the board
bool check_win(char board[6][7], char player) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      if (board[i][j] == player) {
        // Check for horizontal wins starting at (i, j)
        bool horiz_win = true;
        for (int k = 1; k < 4; k++) {
          if (j + k >= 7 || board[i][j + k] != player) {
            horiz_win = false;
          }
        }
        // Check for vertical wins starting at (i, j)
        bool vert_win = true;
        for (int k = 1; k < 4; k++) {
          if (i + k >= 6 || board[i + k][j] != player) {
            vert_win = false;
          }
        }
        // Check for diagonal wins starting at (i, j)
        bool diag_win = true;
        for (int k = 1; k < 4; k++) {
          if (i + k >= 6 || j + k >= 7 || board[i + k][j + k] != player) {
            diag_win = false;
          }
        }
        // Check for back -diagonal wins starting at (i, j)
        bool back_diag_win = true;
        for (int k = 1; k < 4; k++) {
          if (i + k >= 6 || j - k < 0 || board[i + k][j - k] != player) {
            back_diag_win = false;
          }
        }
        if (horiz_win || vert_win || diag_win || back_diag_win) {
          return true;
        }
      }
    }
  }
  return false;
}
// print_board(board) prints the given board to the screen
void print_board(char board[6][7]) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      if (board[i][j] == 'X' || board[i][j] == 'O') {
        printf("%c", board[i][j]);
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}

int main(void) {
  char board[6][7] = {
    ".......",
    ".......",
    ".......",
    ".......",
    ".......",
    "......."
  };
  char player = 'X';
  int move;
  for (move = 0; move < 6 * 7; move++) {
    printf("Enter the column that player %c wants to play in: ", player);
    int col;
    int ret = scanf("%d", & col);
    // Check if input was invalid
    if (ret < 1 || col < 0 || col >= 7) {
      break;
    }
    if (make_move(board, col, player)) {
      print_board(board);
      if (check_win(board, player)) {
        printf("Player %c wins!\n", player);
        break;
      }
      if (player == 'X') {
        player = 'O';
      } else {
        player = 'X';
      }
    } else {
      printf("Illegal move , try again.\n");
      move--;
    }
  }
  if (move == 6 * 7) {
    printf("Tie game.\n");
  }
  char test1[6][7] = {
    ".......",
    ".......",
    "X......",
    "X.....O",
    "X.....O",
    "X.....O"
  };
  assert(check_win(test1, 'X'));
  assert(!check_win(test1, 'O'));
  char test2[6][7] = {
    ".......",
    ".......",
    "O...OO.",
    "X..OXX.",
    "XXOXOX.",
    "XOXOOOX"
  };
  assert(!check_win(test2, 'X'));
  assert(check_win(test2, 'O'));
  char test3[6][7] = {
    ".......",
    ".......",
    ".......",
    ".......",
    ".......",
    "XXXXOOO"
  };
  assert(check_win(test3, 'X'));
  assert(!check_win(test3, 'O'));
  char test4[6][7] = {
    "....OXO",
    "....XOX",
    "...XOXO",
    "...XXOX",
    "...OOXO",
    "..OXXOX"
  };
  assert(check_win(test4, 'X'));
  assert(!check_win(test4, 'O'));
}
