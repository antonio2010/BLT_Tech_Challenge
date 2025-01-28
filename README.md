# BLT_Tech_Challenge
# Timer-Based LED Control for Adafruit Feather 32u4


## Description
This application utilizes the 16-bit Timer1 on the Adafruit Feather 32u4 to control two LEDs:

1. **LED1** toggles within 30ms of the timer count reaching 65000.
2. **LED2** blinks 5 times every 3 seconds. Each blink is spaced enough to be easily visible.


The timer operates in a free-running mode with an 8x prescaler.

## How It Works

1. Timer1 runs in normal mode with an 8x prescaler.
2. Interrupts track Timer1 overflow to maintain a free-running timer count.
3. The first LED toggles based on the Timer1 count reaching 65000.
4. The second LED blinks 5 times every 3 seconds based on elapsed time.

## Prerequisites

- Adafruit Feather 32u4
- AVR GCC toolchain
- `avrdude` for flashing

## File Contents
- `main.c`: The application code.
- `Makefile`: Build and flashing instructions.


## Compilation and Flashing
1. **Compile the code**:
   make
2. **Flash the Code**:
   make flash
3. **Clean the Directory**:
   make clean