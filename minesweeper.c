#include "minesweeper.h"
#include <assert.h>


//////////////////////////////////////
// DO NOT CHANGE THESE CONSTANTS:
const char UNREVEALED = ' ' ;
const char REVEALED[9] = "012345678";
const char FLAG = 'F';
const char MINE = '*';
//////////////////////////////////////

bool flag(struct ms_board *b, int x, int y) {
  assert(b);
  assert(1 <= x);
  assert(x <= b->width);
  assert(1 <= y);
  assert(y <= b->height);
  int pos = (y-1) * b->width + x - 1;
  if (b->board[pos] == UNREVEALED) {
    b->board[pos] = FLAG;
    return true;
  } else if (b->board[pos] == FLAG) {
    b->board[pos] = UNREVEALED;
    return true;
  }
  return false;
}

// add_mines(x, y, z, b) returns int z counting the number of
//   times the (x, y) corrdinates correspond to mines
// Effects: returns int value
int ad_mines(int x, int y, int z, struct ms_board *b) {
  for (int i = 0; i < b->num_mines; i++) {
    if (x == b->mines[i].x && y == b->mines[i].y) {
      //trace_int(x);
      //trace_int(b->mines[i].x);
      z++;
    }
  }
  //trace_int(z);
  return z;
}

bool reveal(struct ms_board *b, int x, int y) {
  assert(b);
  assert(1 <= x);
  assert(x <= b->width);
  assert(1 <= y);
  assert(y <= b->height);
  int pos = (y-1) * b->width + x - 1;
  if (b->board[pos] == UNREVEALED) {
    for (int i = 0; i < b->num_mines; i++) {
      if (x == b->mines[i].x && y == b->mines[i].y) {
        b->board[pos] = MINE;
        return false;
      }
    }
    int z = 0;
    //finding adjacent
    if (x == 1 && y == 1) {
      z = ad_mines(x+1, y, z, b);
      z = ad_mines(x, y+1, z, b);
      z = ad_mines(x+1, y+1, z, b);
    } else if (x == 1 && y != b->height) {
      //trace_msg(hi);
      z = ad_mines(x, y-1, z, b);
      z = ad_mines(x+1, y-1, z , b);
      z = ad_mines(x+1, y, z, b);
      z = ad_mines(x, y+1, z, b);
      z = ad_mines(x+1, y+1, z, b);
    } else if (x == 1 && y == b->height) {
      //trace_msg(hi);
      z = ad_mines(x, y-1, z, b);
      z = ad_mines(x+1, y-1, z, b);
      z = ad_mines(x+1, y, z, b);
    } else if (x == b->width && y == 1) {
      //trace_msg(hi);
      z = ad_mines(x-1, y, z, b);
      z = ad_mines(x-1, y+1, z, b);
      z = ad_mines(x, y+1, z, b);
    } else if (x == b->width && y != b->height) {
      //trace_msg(hi);
      z = ad_mines(x, y-1, z, b);
      z = ad_mines(x-1, y-1, z, b);
      z = ad_mines(x-1, y, z, b);
      z = ad_mines(x-1, y+1, z, b);
      z = ad_mines(x, y+1, z, b);
    } else if (x == b->width && y == b->height) {
      //trace_msg(hi);
      z = ad_mines(x, y-1, z, b);
      z = ad_mines(x-1, y, z, b);
      z = ad_mines(x-1, y-1, z, b);
    } else if (y == 1 && x != 1 && x != b->width) {
      //trace_msg(hi);
      z = ad_mines(x-1, y, z, b);
      z = ad_mines(x-1, y+1, z, b);
      z = ad_mines(x, y+1, z, b);
      z = ad_mines(x+1, y+1, z, b);
      z = ad_mines(x+1, y, z, b);
    } else if (y == b->height && x != 1 && x != b->width) {
      //trace_msg(hi);
      z = ad_mines(x-1, y, z, b);
      z = ad_mines(x-1, y-1, z, b);
      z = ad_mines(x, y-1, z, b);
      z = ad_mines(x+1, y-1, z, b);
      z = ad_mines(x+1, y, z, b);
    } else {
      //trace_msg(hi);
      z = ad_mines(x-1, y-1, z, b);
      z = ad_mines(x, y-1, z, b);
      z = ad_mines(x+1, y-1, z, b);
      z = ad_mines(x+1, y, z, b);
      z = ad_mines(x+1, y+1, z, b);
      z = ad_mines(x, y+1, z, b);
      z = ad_mines(x-1, y+1, z, b);
      z = ad_mines(x-1, y, z, b);
    }
    //trace_int(z);
    if (z == 0) {
      b->board[pos] = REVEALED[z];
      //reveal() recursion
      if (x == 1 && y == 1) {
        reveal(b, x+1, y);
        reveal(b, x, y+1);
        reveal(b, x+1, y+1);
      } else if (x == 1 && y != b->height) {
        //trace_msg(hi);
        reveal(b, x, y-1);
        reveal(b, x+1, y-1);
        reveal(b, x+1, y);
        reveal(b, x, y+1);
        reveal(b, x+1, y+1);
      } else if (x == 1 && y == b->height) {
        //trace_msg(hi);
        reveal(b, x, y-1);
        reveal(b, x+1, y-1);
        reveal(b, x+1, y);
      } else if (x == b->width && y == 1) {
        //trace_msg(hi);
        reveal(b, x-1, y);
        reveal(b, x-1, y+1);
        reveal(b, x, y+1);
      } else if (x == b->width && y != b->height) {
        //trace_msg(hi);
        reveal(b, x, y-1);
        reveal(b, x-1, y-1);
        reveal(b, x-1, y);
        reveal(b, x-1, y+1);
        reveal(b, x, y+1);
      } else if (x == b->width && y == b->height) {
        //trace_msg(hi);
        reveal(b, x, y-1);
        reveal(b, x-1, y);
        reveal(b, x-1, y-1);
      } else if (y == 1 && x != 1 && x != b->width) {
        //trace_msg(hi);
        reveal(b, x-1, y);
        reveal(b, x-1, y+1);
        reveal(b, x, y+1);
        reveal(b, x+1, y+1);
        reveal(b, x+1, y);
      } else if (y == b->height && x != 1 && x != b->width) {
        //trace_msg(hi);
        reveal(b, x-1, y);
        reveal(b, x-1, y-1);
        reveal(b, x, y-1);
        reveal(b, x+1, y-1);
        reveal(b, x+1, y);
      } else {
        //trace_msg(hi);
        reveal(b, x-1, y-1);
        reveal(b, x, y-1);
        reveal(b, x+1, y-1);
        reveal(b, x+1, y);
        reveal(b, x+1, y+1);
        reveal(b, x, y+1);
        reveal(b, x-1, y+1);
        reveal(b, x-1, y);
      }
      //
      return true;
    } else {
      b->board[pos] = REVEALED[z];
      return true;
    }
  } else {
    return false;
  }
}

// mine_coord(x, y, b) returns true if the (int x, int y) 
//   coordinates correspond to mine coordinates
// Effects: returns bool value
bool mine_coord(int x, int y, const struct ms_board *b) {
  for (int i = 0; i < b->num_mines; i++) {
    if (x == b->mines[i].x && y == b->mines[i].y) {
      return true;
    }
  }
  return false;
}

bool game_won(const struct ms_board *b) {
  assert(b);
  assert(b->width > 0);
  assert(b->height > 0);
  for (int i = 1; i < b->width; i++) {
    for (int j = 1; j < b->height; j++) {
      int pos = b->board[(j-1) * b->width + i - 1];
      if (b->board[pos] == UNREVEALED || b->board[pos] == FLAG) {
        if (!mine_coord(i, j, b)) {
          return false;
        }
      } else if (b->board[pos] != MINE) {
        if (mine_coord(i, j, b)) {
          return false;
        }
      }
    }
  }
  return true;
}

bool game_lost(const struct ms_board *b) {
  assert(b);
  assert(b->width > 0);
  assert(b->height > 0);
  for (int i = 1; i < b->width; i++) {
    for (int j = 1; j < b->height; j++) {
      int pos = b->board[(j-1) * b->width + i - 1];
      if (b->board[pos] == MINE) {
        return true;
      }
    }
  }
  return false;
}

