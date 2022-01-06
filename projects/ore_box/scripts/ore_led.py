#!/usr/bin/env python3
# Minecraft specific lights for orebox project
# Benjamin Harder
# Cycles through various colors for the orecube

import RPi.GPIO as GPIO
import time
from rpi_ws281x import *
import os

# LED strip configuration:
LED_COUNT      = 7      # Number of LED pixels.
LED_PIN        = 18      # GPIO pin connected to the pixels (18 uses PWM!).
#LED_PIN        = 10      # GPIO pin connected to the pixels (10 uses SPI /dev/spidev0.0).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 10      # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 255     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)
LED_CHANNEL    = 0       # set to '1' for GPIOs 13, 19, 41, 45 or 53

# Use the Broadcom SOC Pin numbers
# Setup the pin with internal pullups enabled and pin in reading mode.
GPIO.setmode(GPIO.BCM)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# set custom colors for the game
coal = Color(0, 0, 0) # Coal
redstone = Color(204, 0, 0) # Redstone
iron = Color(204, 153, 153) # Iron
gold = Color(255, 204, 0) # Gold
emerald = Color(0, 204, 0) # Emerald
diamond = Color(51, 204, 255) # Diamond

def ore_colors_in(strip, r, g, b, wait_ms=100, iterations=1):
    """Draw rainbow that fades across all pixels at once."""
    for j in range(100):
        for i in range(strip.numPixels()):
            strip.setPixelColor(i, Color(int(r * (j/100)),  int(g * (j/100)), int(b * (j/100))))
        strip.show()
        time.sleep(wait_ms/1000.0)

def ore_colors(strip, colors, wait_ms=500, iterations=1):
    """Draw rainbow that fades across all pixels at once."""
    for j in range(100):
        for i in range(strip.numPixels()):
            strip.setPixelColor(i, colors)
        strip.show()
        time.sleep(wait_ms/1000.0)

def ore_colors_out(strip, r, g, b, wait_ms=200, iterations=1):
    """Draw rainbow that fades across all pixels at once."""
    for j in range(100):
        for i in range(strip.numPixels()):
            strip.setPixelColor(i, Color(int(r * (1-(j/100))),  int(g * (1-(j/100))), int(b * (1-(j/100)))))
        strip.show()
        time.sleep(wait_ms/1000.0)

def Shutdown(channel):
    """Shutdown the pi and turn off the led's """
    print("Shutting Down")
    time.sleep(2)
    for i in range(strip.numPixels()):
        strip.setPixelColor(i, Color(0, 0, 0))
        strip.show()
    os.system('sudo shutdown -h now')

# Main program logic follows:
if __name__ == '__main__':
   
    # Add our function to execute when the button pressed event happens
    GPIO.add_event_detect(21, GPIO.FALLING, callback=Shutdown, bouncetime=2000)

    # Create NeoPixel object with appropriate configuration.
    strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
    # Intialize the library (must be called once before other functions).
    strip.begin()

    while 1:
        print ('Cycle through ore colors.')
        # redstone
        ore_colors_in(strip, 204, 0, 0)
        ore_colors(strip, redstone)
        ore_colors_out(strip, 204, 0, 0)
        # iron
        ore_colors_in(strip, 204, 153, 153)
        ore_colors(strip, iron )
        ore_colors_out(strip, 204, 153, 153)
        # gold
        ore_colors_in(strip, 255, 204, 0)
        ore_colors(strip, gold )
        ore_colors_out(strip, 255, 204, 0)
        # emerald
        ore_colors_in(strip, 0, 204, 0)
        ore_colors(strip, emerald)
        ore_colors_out(strip, 0, 204, 0)
        # diamond
        ore_colors_in(strip, 51, 204, 255)
        ore_colors(strip, diamond )
        ore_colors_out(strip, 51, 204, 255)
