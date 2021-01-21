#include <life.h>

GameOfLife::GameOfLife() {
    this->reset();
}

void GameOfLife::reset() {
    for (int i = 0; i < BOARD_SIZE; i++) memset(this->board[i], 0, BOARD_SIZE);
}

int GameOfLife::countNeighbours(int x, int y) {
    // Look at the LSB, we use the rest of the bits to indicate colour.
    int count;
    for (int y1 = y - 1; y1 <= y + 1; y1++)
        for (int x1 = x - 1; x1 <= x + 1; x1++)
          if (IS_LIT(this->board[(y1 + BOARD_SIZE) % BOARD_SIZE][(x1 + BOARD_SIZE) % BOARD_SIZE]))
            count++;
    return count - (IS_LIT(this->board[x][y]));
}

void GameOfLife::evolve() {
    Board newboard;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; x < BOARD_SIZE; y++) {
            int neighbours = this->countNeighbours(x, y);
            newboard[x][y] = (neighbours == 3 || neighbours == 2 && this->board[x][y]);
        }
    }
    this->updateBoard(newboard);
}

void GameOfLife::updateBoard(Board newboard) {
    memcpy(this->board, newboard, BOARD_SIZE * BOARD_SIZE);
}

void GameOfLife::writeColourIndices(int destination[]) {
    int counter = 0;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            destination[counter++] = COLOUR_INDEX(this->board[x][y]);
        }
    }
}