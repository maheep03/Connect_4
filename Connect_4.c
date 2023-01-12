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
// first_capital(str, n) returns the first capital letter in str;
// returns 0 if str contains no capital letters
// requires: str is a string of length n
// str contains only lower -case and upper -case letters
// all lower -case letters appear before upper -case letters
char first_capital(const char str[], int n) {
  int lo = 0;
  int hi = n - 1;
  // If no characters are capitals
  if (n == 0 || islower(str[hi])) {
    return 0;
  }
  // If all characters are capitals
  if (isupper(str[lo])) {
    return str[lo];
  }
  while (hi != lo + 1) {
    int mid = (hi + lo) / 2;
    if (isupper(str[mid])) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  return str[hi];
}
// deepest_substring(str, out) updates out to be the deepest substring of
// str; the first is used if multiple possibilities exist
// requires:
// str is a string with balanced parenthesis
// out points to enough memory to store the deepest substring of str
void deepest_substring(const char str[], char out[]) {
  int max_depth = 0;
  const char * deepest_substring = str;
  int cur_depth = 0;
  // Find deepest substring
  while ( * str != '\0') {
    if ( * str == '(') {
      cur_depth++;
      if (cur_depth > max_depth) {
        max_depth = cur_depth;
        deepest_substring = str + 1;
      }
    } else if ( * str == ')') {
      cur_depth--;
    }
    str++;
  }
  // Copy deepest substring into out
  str = deepest_substring;
  while ( * str != ')' && * str != '\0') {
    * out = * str;
    str++;
    out++;
  }
  * out = '\0';
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