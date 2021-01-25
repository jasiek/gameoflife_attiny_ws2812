#include <Arduino.h>
#include <string.h>
#include <board.h>
#define DECAY(x) ((x < 4) ? 0 : (((x >> 1) - 1) << 1))

struct GameOfLife {
    public:
    GameOfLife();
    void init(long long*);
    void evolve();
    byte getColourIndex(byte);
#ifndef __AVR_ATtiny85__
    void debug(Print&);
#endif
    bool isFinished();

    inline byte countNeighbours(byte, byte);
    inline void updateBoard(Board);

    Board board;
};
