#include <Arduino.h>
#include <unity.h>
#include "life.h"

// life.cpp

void test_init(void) {
  GameOfLife g;
  unsigned long long all_lit = 18446744073709551615LL;

  g.init(&all_lit);
  for (byte x = 0; x < BOARD_SIZE; x++)
    for (byte y = 0; y < BOARD_SIZE; y++)
      TEST_ASSERT_EQUAL(1, g.board.getLit(x, y));
}

void test_count_neighbours(void) {
  GameOfLife g;
  unsigned long long all_lit = 18446744073709551615LL;

  g.init(&all_lit);
  for (byte x = 0; x < BOARD_SIZE; x++)
    for (byte y = 0; y < BOARD_SIZE; y++)
      TEST_ASSERT_EQUAL(8, g.countNeighbours(x, y));

  g.board.clearBoard();
  for (byte x = 0; x < BOARD_SIZE; x++)
    for (byte y = 0; y < BOARD_SIZE; y++)
      TEST_ASSERT_EQUAL(0, g.countNeighbours(x, y));
}

// board.cpp

void test_colorval(void) {
  Board board;
  board.clearBoard();

  for (byte x = 0; x < BOARD_SIZE; x++)
    for (byte y = 0; y < BOARD_SIZE; y++) {
      TEST_ASSERT_EQUAL(0, board.colorval(x, y));
      for (byte c = 0; c < 8; c++) {
	board.setcolorval(x, y, c);
	TEST_ASSERT_EQUAL(c, board.colorval(x, y));
      }
    }
}

void test_decay(void) {
  Board board;

  memset(board.storage, 0xff, BYTES_OF_STORAGE);
  
  for (int decayedValue = 7; decayedValue > -1; decayedValue--) {
    for (byte x = 0; x < BOARD_SIZE; x++)
      for (byte y = 0; y < BOARD_SIZE; y++)
	TEST_ASSERT_EQUAL(decayedValue, board.colorval(x, y));
    board.decayAll();
  }

    for (byte x = 0; x < BOARD_SIZE; x++)
      for (byte y = 0; y < BOARD_SIZE; y++)
	TEST_ASSERT_EQUAL(0, board.colorval(x, y));
  
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_colorval);
  RUN_TEST(test_decay);
  RUN_TEST(test_init);
  RUN_TEST(test_count_neighbours);
}

void loop() {
  UNITY_END();
}
