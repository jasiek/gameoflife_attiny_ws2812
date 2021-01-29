#include <datatypes.h>

#define BOARD_SIZE 8
#define BITS_PER_PIXEL 3
#define BYTES_OF_STORAGE BOARD_SIZE * BOARD_SIZE * BITS_PER_PIXEL / 8

struct Board {
  byte storage[BYTES_OF_STORAGE];

  byte getLit(byte, byte);
  void setLit(byte, byte, byte);
  byte getColourIdx(byte, byte);
  void setColourIdx(byte, byte, byte);
  void clearBoard();
  void decayAll();
  void copyFrom(Board &);

private:
  byte colorval(byte, byte);
  void setcolorval(byte, byte, byte);
};
