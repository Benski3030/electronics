# LED Volleyball

## Overview

This project aims to make an LED-backlit silhouette of a volleyball as a Christmas present. 
The frame will be 3D printed, while An Arduino microcontroller will manage the electronics. 
The LEDs can be controlled with an IR remote and receiver pair.  

### Materials

[Arduino Nano] (https://store-usa.arduino.cc/products/arduino-nano?selectedStore=us)

[LED Strip] (https://www.amazon.com/gp/product/B07CBS3CN7/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)

[IR Receiver] (https://www.amazon.com/gp/product/B0816P2545/ref=ppx_yo_dt_b_asin_title_o03_s01?ie=UTF8&psc=1)

[Capacitors] (https://www.amazon.com/gp/product/B081PT78Y5/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1)

[Female Power Jack Adapter] (https://www.amazon.com/gp/product/B011YKCK5M/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)

[Thin lexan] (https://www.amazon.com/gp/product/B00520AR9C/ref=ppx_yo_dt_b_asin_title_o03_s01?ie=UTF8&psc=1)

### Code
1. I had a really hard time getting the IR receiver to work consistently, it turns out that the library I was using was out of date.  Moving to the `IRemote` library resolved this.
2. Make sure to use the serial print out as much as possible for debugging.
3. The LEDs worked great once everything was set up.
4. The more complicated animations like the theaterchase took all of the arduino resources, meaning the remote would not work at the same time.
5. It might be possible to control the LEDs via a second Arduino.  

### Assembly
1. Glue the volleyball to the electronics housing
2. Wind the LED strip through the housing
3. Solder and wire up the electronics
4. Attach the back base plate, this can be snap fit
5. Sand the lexan with >200 grit sand paper
6. Glue it and the ring to the outside of the volleyball
7. Hot glue a back on it.
8. Enjoy!

### Conclusion
I was happy with this project, and it was one of the more complicated builds I've undertaken so far.

#### Wins
1. Going from concept to product was less than two weeks
2. My Fusion360 skills are improving
3. Moved away from a breadboard to actually soldering components
4. Arduino code is becoming more familar
5. The end result is pretty cool  

#### Improvements

1. Try to build to create a better model that relies on mechanical attachments insteead of chemical (aka glue.)
2. Create a better housing for the electronics, they're all cramed together
3. Try to use a protoboard for the solder attachments
4. Learn more about how neopixels and LEDs work, there was a lot of copy and pasting
5. Print out a 3d print tolerance test and start using it
6. Had issues with bed adhesion, look into that in the future
