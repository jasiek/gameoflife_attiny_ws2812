#include <board.h>
#include <string.h>

#define COORDS(x, y) (x + (y / 2) * BOARD_SIZE)

byte Board::getLit(register byte x, register byte y) {
  return this->cells[COORDS(x, y)].getLit(y);
}

void Board::setLit(register byte x, register byte y, register byte val) {
  this->cells[COORDS(x, y)].setLit(y, val);
}

byte Board::getColourIdx(register byte x, register byte y) {
  return this->cells[COORDS(x, y)].getColourIdx(y);
}

void Board::setColourIdx(register byte x, register byte y, register byte val) {
  this->cells[COORDS(x, y)].setColourIdx(y, val);
}

void Board::clearBoard() {
  memset(this->cells, 0, BOARD_SIZE * BOARD_SIZE / 2);
}

void Board::decayAll() {
  for (register byte i = 0; i < BOARD_SIZE * BOARD_SIZE / 2; i++) {
    this->cells[i].decay();
  }
}

void Board::copyFrom(Board &board) {
  for (register byte i = 0; i < BOARD_SIZE * BOARD_SIZE / 2; i++) {
    this->cells[i] = board.cells[i];
  }
}
