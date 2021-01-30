#include <Arduino.h>
#include <unity.h>
#include "board.h"

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
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_colorval);
  RUN_TEST(test_decay);
}

void loop() {
  UNITY_END();
}
