#include <Arduino.h>
#include <FastLED.h>
#include <life.h>

#define NUM_LEDS BOARD_SIZE * BOARD_SIZE
#define CHIPSET WS2812
#define COLOR_ORDER GRB
#define LED_PIN 10

unsigned long colour_map[] = {
  CRGB::Black,
  CRGB::DarkBlue,
  CRGB::Blue,
  CRGB::Turquoise,
  CRGB::Green,
  CRGB::GreenYellow,
  CRGB::Yellow,
  CRGB::Orange,
  CRGB::Red,
  CRGB::White
};

CRGB leds[NUM_LEDS];

GameOfLife game;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
  for (byte i = 0; i < NUM_LEDS; i++) leds[i] = colour_map[5];
  FastLED.show();
  game.init(8560);
  //game.init(1983);
  game.debug(Serial);
}

byte colours[NUM_LEDS];
void loop() {
  while (1) {
    for (byte i = 0; i < NUM_LEDS; i++) colours[i] = colour_map[0];
    game.writeColourIndices(colours);
    for (byte i = 0; i < NUM_LEDS; i++) leds[i] = colour_map[colours[i]];
    FastLED.show();
    delay(100);
    game.debug(Serial);
    game.evolve();
  }
}