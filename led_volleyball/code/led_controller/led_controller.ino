/* 
Led Volleyball 
Creat and IR controlled LED Neopixel strip
Benjamin Harder 12/20/221
*/

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

#define DECODE_NEC
#define RECV_PIN 2
#define LED_PIN 6 // LED on pin 6
#define LED_COUNT 144 //LED count

// Declare neopixel strip object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// device setup
void setup() {
  strip.begin(); // start leds
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200); // for debugging
  // Just to know which program is running on my Arduino
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.print(F("at pin "));
  Serial.println(IR_RECEIVE_PIN);
}

// loop when running
void loop() {
  if (IrReceiver.decode()) {

    // Print a short summary of received data
    IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();
    IrReceiver.resume(); // Enable receiving of the next value

    // inner loop to run LED commands
    if (IrReceiver.decodedIRData.command == 0x10) {
      colorWipe(strip.Color(255, 0, 0), 10); //Red
    } else if (IrReceiver.decodedIRData.command == 0x11) {
      colorWipe(strip.Color(0, 255, 0), 10); // Green
    } else if (IrReceiver.decodedIRData.command == 0x12) {
      colorWipe(strip.Color(0, 0, 255), 10); //Blue
    } else if (IrReceiver.decodedIRData.command == 0x13) {
      colorWipe(strip.Color(128, 0, 128), 10); //Purple
    } else if (IrReceiver.decodedIRData.command == 0x14) {
      colorWipe(strip.Color(255, 255, 0), 10); //Yellow
    } else if (IrReceiver.decodedIRData.command == 0x15) {
      colorWipe(strip.Color(220, 220, 220), 10); //White
    } else if (IrReceiver.decodedIRData.command == 0x16) {
      colorWipe(strip.Color(255, 69, 0), 10); //Orange
    } else if (IrReceiver.decodedIRData.command == 0x18) {
      rainbow(10);
    } else if (IrReceiver.decodedIRData.command == 0x1A) {
      theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness
    }
  }
}


// led effect functions

// one directional color wipe
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                           
  }
}

// one color theater chase
void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 3000000; a++) { 
    for (int b = 0; b < 3; b++) { 
      strip.clear();         
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); 
      }
      strip.show();
      delay(wait);  
    }
  }
}

// rainbow fade in and out between colors
void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// theater chase, but with rainbow colors
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;    
  for (int a = 0; a < 3000000; a++) { 
    for (int b = 0; b < 3; b++) { 
      strip.clear();         
      for (int c = b; c < strip.numPixels(); c += 3) {
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); 
        strip.setPixelColor(c, color); 
      }
      strip.show();                
      delay(wait);                 
      firstPixelHue += 65536 / 90; 
    }
  }
}
