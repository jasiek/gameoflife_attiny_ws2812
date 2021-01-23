#include <Arduino.h>
#include <FastLED.h>
#include <life.h>

#define NUM_LEDS BOARD_SIZE * BOARD_SIZE
#define CHIPSET WS2812
#define COLOR_ORDER GRB
#define LED_PIN 10
#define INITIAL_STATE 2779831273LL

unsigned long colour_map[] = {
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
long long state = INITIAL_STATE;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(5);

  game.init(state);
  game.debug(Serial);
}

byte colours[NUM_LEDS];
void loop() {
  while (!game.isFinished()) {
    game.writeColourIndices(colours);
    for (byte i = 0; i < NUM_LEDS; i++) leds[i] = colour_map[colours[i]];
    game.debug(Serial);
    FastLED.show();
    delay(33);
    game.evolve();
  }
  game.init(state++);
}