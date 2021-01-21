#include <life.h>

GameOfLife::GameOfLife() {
    this->reset();
}

void GameOfLife::init(int matrix) {
    // tested
    for (byte x = 2; x < 6; x++) {
        for (byte y = 2; y < 6; y++) {
            this->board[x][y] = matrix & 1;
            matrix /= 2;
        }
    }
}

void GameOfLife::reset() {
    // tested
    memset(this->board, 0, BOARD_SIZE * BOARD_SIZE);
}

byte GameOfLife::countNeighbours(byte x, byte y) {
    // Look at the LSB, we use the rest of the bits to indicate colour.
    byte count = 0;
    // These need to be chars (signed) for the indexing to work.
    for (char x1 = x - 1; x1 <= x + 1; x1++)
        for (char y1 = y - 1; y1 <= y + 1; y1++)
          if (IS_LIT(this->board[(x1 + BOARD_SIZE) % BOARD_SIZE][(y1 + BOARD_SIZE) % BOARD_SIZE]))
            count++;
    return count - (IS_LIT(this->board[x][y]));
}

void GameOfLife::evolve() {
    // tested
    Board newboard;
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
            byte neighbours = this->countNeighbours(x, y);
            newboard[x][y] = (neighbours == 3 || (neighbours == 2 && this->board[x][y]));
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
                destination[counter] = 8;
            }
            counter++;
        }
    }
}

void GameOfLife::debug(Print &p) {
    p.println("game state:");
    for (byte x = 0; x < BOARD_SIZE; x++) {
        for (byte y = 0; y < BOARD_SIZE; y++) {
            p.print(this->board[x][y]);
            p.print(", ");
        }
        p.println();
    }
}