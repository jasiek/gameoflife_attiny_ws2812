#include <Arduino.h>
#include <string.h>
#include "board.h"

struct GameOfLife {
    public:
    GameOfLife();
    void init(unsigned long long);
    void evolve();
    byte getColourIndex(byte);
#ifndef __AVR_ATtiny85__
    void debug(Print&);
#endif
    bool isFinished();

    inline byte countNeighbours(byte, byte);
    inline void updateBoard(Board);

    Board board;
    Board newboard;
};
