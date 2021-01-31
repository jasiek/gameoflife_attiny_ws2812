#include <board.h>
#include <string.h>

// DONE
inline byte chunk(/* register */ byte x, /* register */ byte y) {
  /*
   * Find a chunk (2 bytes) which includes the 3 bit value we're interested in.
   * The value can occur at a boundary => we need 16 bits.
   */
  /* register */ byte bit_offset = BITS_PER_PIXEL * (x + y * BOARD_SIZE);
  return bit_offset / 8;
}

// DONE
inline byte shiftval(/* register */ byte x, /* register */ byte y) {
  /*
   * Suppose we have the 16 bits we're interested in at hand. By how much
   * do we need to shift to the right to be able to mask the 3 bit value
   * and retrieve it?
   */

  // How many bits are there to the left of this chunk?
  /* register */ byte left_bit_offset = BITS_PER_PIXEL * (x + y * BOARD_SIZE);
  left_bit_offset %= 8;

  return 16 - 3 - left_bit_offset;
}

// DONE
byte Board::colorval(/* register */ byte x, /* register */ byte y) {
  /* register */ word theChunk = 0;
  /* register */ byte chunkNum = chunk(x, y);
  theChunk = this->storage[chunkNum];
  theChunk <<= 8;
  theChunk += this->storage[chunkNum + 1];
  theChunk >>= shiftval(x, y);
  return (byte)(theChunk & 7);
}

void Board::setcolorval(/* register */ byte x, /* register */ byte y, /* register */ byte val) {
  // copy chunk
  /* register */ word theChunk = 0;
  /* register */ byte chunkNum = chunk(x, y);
  theChunk = this->storage[chunkNum];
  theChunk <<= 8;
  theChunk += this->storage[chunkNum + 1];
  
  // knock out masked bits with & (11000111111)
  /* register */ byte left_bit_offset = BITS_PER_PIXEL * (x + y * BOARD_SIZE);
  left_bit_offset %= 8;

  word mask = 7;
  mask <<= 16 - (left_bit_offset + 3); // is this right?
  theChunk &= ~mask;

  // put bits in using |
  mask = 0;
  mask = val;
  mask <<= 16 - (left_bit_offset + 3);
  theChunk |= mask;

  // save back
  this->storage[chunkNum + 1] = theChunk & 0xff;
  theChunk >>= 8;
  this->storage[chunkNum] = theChunk & 0xff;
}

// DONE
byte Board::getLit(/* register */ byte x, /* register */ byte y) {
  return this->colorval(x, y) == 7;
}

// DONE
void Board::setLit(/* register */ byte x, /* register */ byte y, /* register */ byte val) {
  this->setcolorval(x, y, val ? 7 : 0);
}

// DONE
byte Board::getColourIdx(/* register */ byte x, /* register */ byte y) {
  return this->colorval(x, y);
}

// DONE
void Board::setColourIdx(/* register */ byte x, /* register */ byte y, /* register */ byte val) {
  return this->setcolorval(x, y, val);
}

// DONE
void Board::clearBoard() {
  memset(this->storage, 0, BYTES_OF_STORAGE);
}

// DONE
void Board::decayAll() {
  // can be optimized?
  for (/* register */ byte x = 0; x < BOARD_SIZE; x++)
    for (/* register */ byte y = 0; y < BOARD_SIZE; y++) {
      /* register */ byte color = this->getColourIdx(x, y);
      if (color > 0) color--;
      this->setColourIdx(x, y, color);
    }
}

// DONE
void Board::copyFrom(Board &board) {
  memcpy(this->storage, board.storage, BYTES_OF_STORAGE);
}
