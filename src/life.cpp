#include <life.h>

GameOfLife::GameOfLife() {
  this->board.clearBoard();
}

void GameOfLife::init(long long *matrix) {
    // we don't care if the incoming value gets modified
    for (register byte x = 0; x < BOARD_SIZE; x++) {
        for (register byte y = 0; y < BOARD_SIZE; y++) {
	  this->board.setLit(x, y, *matrix & 1);
	  *matrix >> 1;
        }
    }
}

byte GameOfLife::countNeighbours(register byte x, register byte y) {
    // Look at the LSB, we use the rest of the bits to indicate colour.
    register byte count = 0;
    // These need to be chars (signed) for the indexing to work.
    for (register char x1 = x - 1; x1 <= x + 1; x1++)
        for (register char y1 = y - 1; y1 <= y + 1; y1++)
	  count += this->board.getLit(
				      (x1 + BOARD_SIZE) % BOARD_SIZE,
	                              (y1 + BOARD_SIZE) % BOARD_SIZE
				      );
    return count - this->board.getLit(x, y);
}

void GameOfLife::evolve() {
    // tested
    Board newboard;
    newboard.clearBoard();
    newboard.copyFrom(this->board);
    newboard.decayAll();
    for (register byte x = 0; x < BOARD_SIZE; x++) {
        for (register byte y = 0; y < BOARD_SIZE; y++) {
            register byte neighbours = this->countNeighbours(x, y);
            // light up what needs to be lit up
            if (neighbours == 3 || (neighbours == 2 && this->board.getLit(x, y))) {
                // colour me red, and light up
	      newboard.setLit(x, y, 1);
	      newboard.setColourIdx(x, y, 8);
            }
        }
    }
    this->board.copyFrom(newboard);
}

bool GameOfLife::isFinished() {
    for (register byte x = 0; x < BOARD_SIZE; x++)
        for (register byte y = 0; y < BOARD_SIZE; y++)
	  if (this->board.getLit(x, y))
                return false;
    return true;
}

#ifndef __AVR_ATtiny85__
void GameOfLife::debug(Print &p) {
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
