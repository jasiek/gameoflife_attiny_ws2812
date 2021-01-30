#ifndef UNIT_TEST
#include <Arduino.h>
#include <FastLED.h>
#include "life.h"

#define NUM_LEDS BOARD_SIZE * BOARD_SIZE
#define CHIPSET WS2812
#define COLOR_ORDER GRB
#define INITIAL_STATE 2779831273LL

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
  CRGB::GreenYellow,
  CRGB::Yellow,
  CRGB::OrangeRed,
  CRGB::Red
};

CRGB leds[NUM_LEDS];

GameOfLife game;

// Interesting states:
// 1989 - loops
// 8560 - glider
// 3754 - end state is a letter D
// 27712 - f pantomime
// 2779831273LL - who knows
// 18446744073709551615LL - all lit
unsigned long long state = INITIAL_STATE;

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
#ifdef DEBUG
  FastLED.setMaxRefreshRate(0, false);
#endif

  game.init(&state);
#ifndef __AVR_ATtiny85__
  Serial.begin(115200);
#endif
}

void loop() {
  while (!game.isFinished()) {
#ifndef __AVR_ATtiny85__
    game.debug(Serial);
#endif
    for (register byte x = 0; x < BOARD_SIZE; x++)
      for (register byte y = 0; y < BOARD_SIZE; y++)
	leds[x * NUM_LEDS + y] = colour_map[game.board.getColourIdx(x, y)];
    FastLED.show();
    delay(33);
    game.evolve();

    delay(1000);
  }
}
#endif
