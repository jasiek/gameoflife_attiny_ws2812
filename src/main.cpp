#ifndef UNIT_TEST
#include <Arduino.h>
#include <FastLED.h>
#include "life.h"

#define NUM_LEDS BOARD_SIZE * BOARD_SIZE
#define CHIPSET WS2812
#define COLOR_ORDER GRB

#ifdef __AVR_ATtiny85__
#define LED_PIN PB0
#else
#define LED_PIN 10
#endif

const unsigned long colour_map[] = {
  CRGB::Black,
  CRGB::DarkBlue,
  CRGB::Blue,
  CRGB::Turquoise,
  CRGB::Green,
  CRGB::Yellow,
  CRGB::OrangeRed,
  CRGB::Red
};

CRGB leds[NUM_LEDS];

GameOfLife game;

// Interesting states:
// 1989 - loops
// 3754 - end state is a letter D
// 131846 - f pantomime
// 235406336 - https://en.wikipedia.org/wiki/Glider_(Conway%27s_Life)
// 970717134848 - Die hard
// 46369272376832 - ?
// 252956460974080 - Acorn
// 16926019738927104 - Lightweight Spaceship
// 18446744073709551615LL - all lit
unsigned long long state = 252956460974080;

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
#ifdef DEBUG
    FastLED.setMaxRefreshRate(0, false);
#endif

  game.init(state);
#ifndef __AVR_ATtiny85__
  Serial.begin(115200);
#endif
}

void displayState() {
  for (register byte x = 0; x < BOARD_SIZE; x++)
    for (register byte y = 0; y < BOARD_SIZE; y++)
      leds[x + y * BOARD_SIZE] = colour_map[game.board.getColourIdx(x, y)];
    FastLED.show();
  delay(100);
}

void loop() {
  displayState();
  
  while (!game.isFinished()) {
#ifndef __AVR_ATtiny85__
    game.debug(Serial);
#endif
    game.evolve();
    displayState();
  }

  game.init(state);
}
#endif
