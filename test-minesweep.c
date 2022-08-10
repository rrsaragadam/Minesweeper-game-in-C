#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "minesweeper.h"

// a very simple assertion-based minesweeper test client

// char_array_equal(a,b,len) returns true if a and b have the same elements
//   (or at least, the first len characters match).
// requires: a, b are valid char arrays
//           len is the length of both a and b
static bool char_array_equal(const char a[], const char b[], int len) {
  assert(len > 0);
  assert(a);
  assert(b);
  for (int i = 0; i < len; ++i) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

int main(void) {//(y-1) * b->width + x - 1;
  struct posn mines[] = {{1,1}};
  char board[]  = {UNREVEALED,UNREVEALED,UNREVEALED,
                   UNREVEALED,UNREVEALED,UNREVEALED, //(3, 2)
                   UNREVEALED,UNREVEALED,UNREVEALED}; //7    
  // blank board, i.e.
  // 123
  //1
  //2
  //3

  char eboard[] = {UNREVEALED, REVEALED[1], UNREVEALED,
                   UNREVEALED, FLAG, UNREVEALED,
                   UNREVEALED, UNREVEALED, UNREVEALED};
  
  char eboard1[] = {UNREVEALED, REVEALED[1], REVEALED[0],
                   REVEALED[1], FLAG, REVEALED[0],
                   REVEALED[0], REVEALED[0], REVEALED[0]};
                   
  // expected board after flag + reveal below
  // 123
  //1 1
  //2 F
  //3
  
  struct ms_board b = {3, 3, board, 1, mines};
  assert(!game_won(&b)); // the mine is not revealed, but neither are the 8 safe tiles.
  assert(!game_lost(&b)); // the mine is not revealed.
  flag(&b, 2, 2); // note: this is not where the mine is
  reveal(&b, 3, 3);
  // test to see the array
  assert(char_array_equal(board, eboard1, 9));
}
