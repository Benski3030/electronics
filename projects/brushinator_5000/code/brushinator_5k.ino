/* 
Benjamin Harder
5/17/23

The code controls a SparkFun APDS-9960 proximity sensor and an Adafruit NeoPixel ring. 
The proximity sensor is set up to detect proximity levels and trigger an interrupt when the proximity 
level is too high or too low. When the interrupt is triggered, it reads the proximity level and 
turns on all the pixels in the NeoPixel ring to blue. Then, it turns off one pixel at a time 
in a clockwise direction until all the pixels are off. After that, the NeoPixel ring flashes 
green five times before turning off all the pixels. 

The function colorWipe() fills the pixels with a specified color, and the function 
interruptRoutine() updates a flag when an interrupt occurs.
*/

//include required libraries
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

//define pins
#define APDS9960_INT 2
#define LED_PIN 13     
#define PIXEL_PIN 6
#define NUM_PIXELS 16

//define constants
#define PROX_INT_HIGH 300
#define PROX_INT_LOW 0
const int BRUSH_TIME = 30000;
int delay_time = (BRUSH_TIME / NUM_PIXELS) * 4; 

//initialize variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint8_t proximity_data = 0;
int isr_flag = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //set pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(APDS9960_INT, INPUT);

  //initialize serial and interrupt
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("---------------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ProximityInterrupt"));
  Serial.println(F("---------------------------------------"));
  attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);

  //initialize apds-9960
  if(apds.init()){
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  //adjust the proximity sensor gain
  if (!apds.setProximityGain(PGAIN_2X)) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  //set proximity interrupt thresholds
  if (!apds.setProximityIntLowThreshold(PROX_INT_LOW)) {
    Serial.println(F("Error writing low threshold"));
  }
  if (!apds.setProximityIntHighThreshold(PROX_INT_HIGH)) {
    Serial.println(F("Error writing high threshold"));
  }

  // Start running the APDS-9960 proximity sensor (interrupts)
  if (apds.enableProximitySensor(true)) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }

  //initialize pixel ring
  pixels.begin();
  pixels.setBrightness(50);
  pixels.clear();
}

void loop() {
  // If interrupt occurs, print out the proximity level
  if (isr_flag == 1) {
    // Read proximity level and print it out
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
    // Reset flag and clear APDS-9960 interrupt 
    isr_flag = 0;
    if (!apds.clearProximityInt()) {
      Serial.println("Error clearing interrupt");
    }
  }
}


//fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
  }
  pixels.show();
  delay(wait);
}

//update flag after an interrupt occurs
void interruptRoutine() {
  isr_flag = 1;
}
