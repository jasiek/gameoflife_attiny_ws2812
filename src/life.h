#include <Arduino.h>
#include <string.h>
#define BOARD_SIZE 8
#define IS_LIT(x) (x & 1)
#define COLOUR_INDEX(x) (x >> 1)
#define DECAY(x) ((x < 4) ? 0 : (((x >> 1) - 1) << 1))

typedef unsigned char Cell;
typedef unsigned char byte;
typedef Cell Board[BOARD_SIZE][BOARD_SIZE];

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

    private:
    inline void clearBoard(Board);
    inline byte countNeighbours(byte, byte);
    inline void updateBoard(Board);
    inline void copyColoursAndDecay(Board);

    Board board;
};
