#include <string.h>
#define BOARD_SIZE 8
#define IS_LIT(x) (x & 1)
#define COLOUR_INDEX(x) ((x & 0xfe) >> 1)

typedef unsigned short int Cell;
typedef Cell Board[BOARD_SIZE][BOARD_SIZE];

class GameOfLife {
    public:
    GameOfLife();
    void reset();
    void evolve();
    void writeColourIndices(int[]);

    private:
    int countNeighbours(int, int);
    void updateBoard(Board);
    Board board;
};