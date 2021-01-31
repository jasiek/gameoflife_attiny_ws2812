
# Game of Life on the ATTINY85

## Motivation

To get game of life working on the smallest MCU I could find in my workshop. My initial idea was to just display the state of the game, but then I realised that the WS2812 is an RGB array, which means you can also display pixels which were lit during previous states of the game.

## Implementation

I've decided to stick with C, as I'm not familiar enough with AVR assembly to implement this. While experimenting I've discovered a number of tools and techniques to make developing palatable on hardware which doesn't have enough space for printf-style debugging.

#### Correctness first, speed and space consumption second

While building this, I've quickly discovered that it will be difficult to debug this easily. To aid in that, I chose to develop a correct implementation first, nail it down, and see what happens. The first implementation made me realise that RAM is a precious commodity on the ATTINY85 (only 512 bytes are available) - and it was exhausted quite quickly. I chose to develop on a more powerful ATMEGA328p (Arduino Uno board) so that it would be easy to debug and write tests. Re-targetting it to an ATTINY85 meant just changing the MCU type and hitting upload.

This resulted in an implementation with about 460 bytes used. When ran, it would hang after a few pixels were displayed. My hypothesis was that I was running out of memory, and resorted to a tool called SIMAVR to determine how much RAM this was really using.

#### Use a simulator if debugging on the chip is too hard

SIMAVR will simulate a number of different Atmel MCUs and exposes a GDB-compatible remote interface. Since the program only results in outputs, it was quite easy to debug it. 

To determine the max amount of RAM used I resorted to the widely known "freshly painted bench" trick. In essence, you fill available memory (in my case, via GDB) with a known pattern (0xff). You then run the program and see how much was overwritten. In my case, the result was quite dramatic as it ended up deep in the .data section which would explain why it halted, despite the implementation seeming correct.

#### Registers are RAM that doesn't cost anything

The ATTINY85 contains 32 8-bit registers which includes three 2-byte registers (X, Y, Z) - a lot more than I needed. Changing all working variables and parameters to register variables meant that no memory would be allocated on the stack for them. This saved a ton.

#### Use every bit

My initial implementation would use the LSB to indicate whether a LED was lit - I later decided to use just 3 bits to represent the state of each cell. The 3 bits would represent the color index to lite the cell up with, and if we were to light up a cell in the current generation, it would have the value 7 (=0b111).

### Summary

RAM use is dominated by the FastLED library. There's a variable (`PixelController<(EOrder)66, 1, 4294967295ul>::init_binary_dithering()::R`) which occupies ~260 bytes, so that may be worth looking at given I don't do any dithering. All calls use register variables, so stack use is minimal.

