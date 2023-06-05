#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <LowPower.h>  // Include Low Power library

// Define pins and constants
#define APDS9960_INT 2
#define LED_PIN 13
#define PIXEL_PIN 6
#define NUM_PIXELS 16

#define PROX_INT_HIGH 300
#define PROX_INT_LOW 0
const int BRUSH_TIME = 30000;
int delay_time = (BRUSH_TIME / NUM_PIXELS) * 4;

// Initialize objects
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;
int isr_flag = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(APDS9960_INT, INPUT);

  Serial.begin(9600);
  Serial.println();
  Serial.println(F("---------------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ProximityInterrupt"));
  Serial.println(F("---------------------------------------"));
  attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);

  if (apds.init()) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  if (!apds.setProximityGain(PGAIN_2X)) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }

  if (!apds.setProximityIntLowThreshold(PROX_INT_LOW)) {
    Serial.println(F("Error writing low threshold"));
  }
  if (!apds.setProximityIntHighThreshold(PROX_INT_HIGH)) {
    Serial.println(F("Error writing high threshold"));
  }

  if (apds.enableProximitySensor(true)) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as output

  pixels.begin();
  pixels.setBrightness(30);  // Lower brightness to save power
  pixels.clear();
}

void loop() {
  if (isr_flag == 1) {
    if (!apds.readProximity(proximity_data)) {
      Serial.println("Error reading proximity value");
    } else {

      Serial.print("Proximity detected! Level: ");
      Serial.println(proximity_data);
      // Turn all the pixels blue
      for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      }
      pixels.show();

      delay(1000);

      // Initialize countdown
      int countdown = NUM_PIXELS;
      // Turn off one pixel at a time clockwise
      while (countdown > 0) {
        // Turn off the next pixel in the ring
        pixels.setPixelColor(countdown - 1, pixels.Color(0, 0, 0));
        pixels.show();
        // Delay before turning off the next pixel
        delay(delay_time);
        countdown--;
      }
      colorWipe(pixels.Color(0, 0, 0), 50);
      // Flash the whole ring green five times
      for (int j = 0; j < 5; j++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 255, 0));
        }
        pixels.show();
        delay(200);
        for (int i = 0; i < NUM_PIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        }
        pixels.show();
        delay(200);
      }
      // Turn off all pixels.
      pixels.clear();
    }
    isr_flag = 0;
    if (!apds.clearProximityInt()) {
      Serial.println("Error clearing interrupt");
    }
  }
  // Let Arduino sleep and wake up every 8 seconds (or longer if suitable).
  // Replace SLEEP_8S with SLEEP_15Ms, SLEEP_30MS, SLEEP_60MS, SLEEP_120MS, SLEEP_250MS, SLEEP_500MS, SLEEP_1S, SLEEP_2S, SLEEP_4S
  // if you need shorter sleep period.
  // Turn off the built-in LED before sleeping
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Going to sleep now");
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  // Turn on the built-in LED after waking up
  digitalWrite(LED_BUILTIN, HIGH);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
  }
  pixels.show();
  delay(wait);
}

void interruptRoutine() {
  isr_flag = 1;
}
