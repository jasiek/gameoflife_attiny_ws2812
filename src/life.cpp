#include <life.h>

GameOfLife::GameOfLife() {
  this->board.clearBoard();
}

void GameOfLife::init(unsigned long long *matrix) {
    // we don't care if the incoming value gets modified
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
	  this->board.setLit(x, y, *matrix & 1);
	  *matrix >>= 1;
        }
    }
}

byte GameOfLife::countNeighbours(byte x, byte y) {
    // Look at the LSB, we use the rest of the bits to indicate colour.
    byte count = 0;
    // These need to be chars (signed) for the indexing to work.
    for (char x1 = x - 1; x1 <= x + 1; x1++)
        for (char y1 = y - 1; y1 <= y + 1; y1++)
	  count += this->board.getLit(
				      (x1 + BOARD_SIZE) % BOARD_SIZE,
	                              (y1 + BOARD_SIZE) % BOARD_SIZE
				      );
    return count - this->board.getLit(x, y);
}

void GameOfLife::evolve() {
    // tested
    this->newboard.clearBoard();
    this->newboard.copyFrom(this->board);
    this->newboard.decayAll();
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
            byte neighbours = this->countNeighbours(x, y);
            // light up what needs to be lit up
            if (neighbours == 3 || (neighbours == 2 && this->board.getLit(x, y))) {
                // colour me red, and light up
	      this->newboard.setLit(x, y, 1);
            }
        }
    }
    this->board.copyFrom(this->newboard);
}

bool GameOfLife::isFinished() {
    for (byte x = 0; x < BOARD_SIZE; x++)
        for (byte y = 0; y < BOARD_SIZE; y++)
	  // Wait until all cells are dark.
	  if (this->board.getColourIdx(x, y))
                return false;
    return true;
}

#ifndef __AVR_ATtiny85__
void GameOfLife::debug(Print &p) {
  p.println();
  for (byte x = 0; x < BOARD_SIZE; x++) {
    for (byte y = 0; y < BOARD_SIZE; y++) {
      p.print(this->board.getLit(x, y) ? "*" : " ");
      p.print(" ");
    }
    p.print(" | ");
    for (byte y = 0; y < BOARD_SIZE; y++) {
      p.print(this->board.getColourIdx(x, y));
      p.print(" ");
    }
    p.println();
  }
}
#endif
