#include <life.h>

GameOfLife::GameOfLife() {
    this->clearBoard(this->board);
}

void GameOfLife::init(long long matrix) {
    // tested
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
            this->board[x][y] = matrix & 1;
            matrix >> 1;
        }
    }
}

void GameOfLife::clearBoard(Board board) {
    // tested
    memset(board, 0, BOARD_SIZE * BOARD_SIZE);
}

byte GameOfLife::countNeighbours(byte x, byte y) {
    // Look at the LSB, we use the rest of the bits to indicate colour.
    byte count = 0;
    // These need to be chars (signed) for the indexing to work.
    for (char x1 = x - 1; x1 <= x + 1; x1++)
        for (char y1 = y - 1; y1 <= y + 1; y1++)
          count += IS_LIT(this->board[(x1 + BOARD_SIZE) % BOARD_SIZE][(y1 + BOARD_SIZE) % BOARD_SIZE]);
    return count - (IS_LIT(this->board[x][y]));
}

void GameOfLife::evolve() {
    // tested
    Board newboard;
    this->clearBoard(newboard);
    this->copyColoursAndDecay(newboard);
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
            byte neighbours = this->countNeighbours(x, y);
            // light up what needs to be lit up
            if (neighbours == 3 || (neighbours == 2 && IS_LIT(this->board[x][y]))) {
                // colour me red, and light up
                newboard[x][y] = (8 << 1) + 1;
            }
        }
    }
    this->updateBoard(newboard);
}

void GameOfLife::copyColoursAndDecay(Board newboard) {
    // copy current colouring, mark all cells as unlit
    // decay all colours on board
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
            newboard[x][y] = DECAY(this->board[x][y]);
        }
    }
}

void GameOfLife::updateBoard(Board newboard) {
    memcpy(this->board, newboard, BOARD_SIZE * BOARD_SIZE);
}

byte GameOfLife::getColourIndex(byte index) {
    return COLOUR_INDEX(this->board[index / BOARD_SIZE][index % BOARD_SIZE]);
}

bool GameOfLife::isFinished() {
    for (byte x = 0; x < BOARD_SIZE; x++)
        for (byte y = 0; y < BOARD_SIZE; y++)
            if (IS_LIT(this->board[x][y]))
                return false;
    return true;
}

#ifndef __AVR_ATtiny85__
void GameOfLife::debug(Print &p) {
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
            p.print(IS_LIT(this->board[x][y]) ? "*" : " ");
            p.print(" ");
        }
        p.print(" | ");
        for (byte y = 0; y < BOARD_SIZE; y++) {
            p.print(COLOUR_INDEX(this->board[x][y]));
            p.print(" ");
        }
        p.println();
    }
}
#endif