# Makefile for Adafruit Feather 32u4
# Target MCU
MCU = atmega32u4

# Target file name
TARGET = main


# Compiler and flags
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=16000000UL

# AVRDUDE settings for flashing
AVRDUDE = avrdude
PROGRAMMER = avr109
PORT = COM3  # Update this to the correct port for your board

# Build rules
all: $(TARGET).hex
$(TARGET).hex: $(TARGET).out
	avr-objcopy -O ihex -R .eeprom $(TARGET).out $(TARGET).hex

$(TARGET).out: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).c

flash: $(TARGET).hex
	$(AVRDUDE) -v -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b 57600 - D -U flash:w:$(TARGET).hex

clean:
	rm -f $(TARGET).out $(TARGET).hex