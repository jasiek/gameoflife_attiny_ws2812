#include <Arduino.h>
#include <FastLED.h>
#include <life.h>

#define NUM_LEDS BOARD_SIZE * BOARD_SIZE
#define CHIPSET WS2812
#define COLOR_ORDER GRB
#define LED_PIN PB1

unsigned long colour_map[] = {
  CRGB::Black,
  CRGB::DarkBlue,
  CRGB::Blue,
  CRGB::Turquoise,
  CRGB::Green,
  CRGB::GreenYellow,
  CRGB::Yellow,
  CRGB::Orange,
  CRGB::Red
};

CRGB leds[NUM_LEDS];

GameOfLife game;

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.show();
}

void loop() {
  while (1) {
    game.evolve();
    int colours[NUM_LEDS];
    game.writeColourIndices(colours);
    for (int i = 0; i < NUM_LEDS; i++) leds[i] = colour_map[colours[i]];
    FastLED.show();
  }
}