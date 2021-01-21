#include <life.h>

GameOfLife::GameOfLife() {
    this->reset();
}

void GameOfLife::init(int matrix) {
    for (byte x = 2; x < 6; x++) {
        for (byte y = 2; y < 6; y++) {
            this->board[x][y] = matrix & 1;
            matrix >> 1;
        }
    }
}

void GameOfLife::reset() {
    memset(this->board, 0, BOARD_SIZE);
}

byte GameOfLife::countNeighbours(byte x, byte y) {
    // Look at the LSB, we use the rest of the bits to indicate colour.
    byte count;
    for (byte y1 = y - 1; y1 <= y + 1; y1++)
        for (byte x1 = x - 1; x1 <= x + 1; x1++)
          if (IS_LIT(this->board[(y1 + BOARD_SIZE) % BOARD_SIZE][(x1 + BOARD_SIZE) % BOARD_SIZE]))
            count++;
    return count - (IS_LIT(this->board[x][y]));
}

void GameOfLife::evolve() {
    Board newboard;
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; x < BOARD_SIZE; y++) {
            byte neighbours = this->countNeighbours(x, y);
            newboard[x][y] = (neighbours == 3 || neighbours == 2 && this->board[x][y]);
        }
    }
    this->updateBoard(newboard);
}

void GameOfLife::updateBoard(Board newboard) {
    memcpy(this->board, newboard, BOARD_SIZE * BOARD_SIZE);
}

void GameOfLife::writeColourIndices(byte destination[]) {
    byte counter = 0;
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
            if (IS_LIT(this->board[x][y])) {
                destination[counter] = 9;
            }
            counter++;
            //destination[counter++] = COLOUR_INDEX(this->board[x][y]);
        }
    }
}