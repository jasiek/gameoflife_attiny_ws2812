#include <2cell.h>

#define BOARD_SIZE 8

struct Board {
  TwoCell cells[BOARD_SIZE * BOARD_SIZE / 2];

  byte getLit(byte, byte);
  void setLit(byte, byte, byte);
  byte getColourIdx(byte, byte);
  void setColourIdx(byte, byte, byte);
  void clearBoard();
  void decayAll();
  void copyFrom(Board &);
};
