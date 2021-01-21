#include <string.h>
#define BOARD_SIZE 8
#define IS_LIT(x) (x & 1)
#define COLOUR_INDEX(x) ((x & 0xfe) >> 1)

typedef unsigned char Cell;
typedef unsigned char byte;
typedef Cell Board[BOARD_SIZE][BOARD_SIZE];

class GameOfLife {
    public:
    GameOfLife();
    void reset();
    void evolve();
    inline void writeColourIndices(byte[]);

    private:
    inline byte countNeighbours(byte, byte);
    inline void updateBoard(Board);
    Board board;
};