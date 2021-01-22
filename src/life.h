#include <Arduino.h>
#include <string.h>
#define BOARD_SIZE 8
#define IS_LIT(x) (x & 1)
#define COLOUR_INDEX(x) (x >> 1)
#define DECAY(x) ((x < 4) ? 0 : (((x >> 1) - 1) << 1))

typedef unsigned char Cell;
typedef unsigned char byte;
typedef Cell Board[BOARD_SIZE][BOARD_SIZE];

class GameOfLife {
    public:
    GameOfLife();
    void init(int);
    void evolve();
    void writeColourIndices(byte[]);
    void debug(Print&);
    bool isFinished();

    private:
    inline void clearBoard(Board);
    inline byte countNeighbours(byte, byte);
    inline void updateBoard(Board);
    inline void copyColoursAndDecay(Board);

    Board board;
};