/*******
  Reference 1: Code for the Textile Game Controller Jam by Social Body Lab, Dames Making Game, & Game Play Lab.
  May 30, 2020 - June 6, 2020.
  This is code follows along the "How to Make an E-Textile Digital Switch" here: https://youtu.be/OHO1NxV-ebw
  The code contains 1 digital switch which lights up the LED ring when activated.
  Circuit Playground Library:
  https://learn.adafruit.com/circuit-playground-lesson-number-0

  Reference 2: Adafruit "A basic everyday NeoPixel strip test program"
  Adafruit_Neopixel Library:https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest/strandtest.ino
*********/

/**Must include the Adafruit_CircuitPlayground.h**/

#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>

int cactusVal;       // Reads the input of the switch, returns either a 0 or 1
int CACTUS_PIN = 3;  // The physical pin that e-textile material is connected to

int skateVal;        // Reads the input of the switch, returns either a 0 or 1
int SKATE_PIN = 1;   // The physical pin that e-textile material is connected to


#define RING_PIN      10   //Pysical pin connected to NP ring
#define RING_COUNT    24  // Number of NP attached to CPX

#define STRIP_PIN    2     //Pysical pin connected to NP strand
#define STRIP_COUNT  90   // Number of NP attached to CPX


Adafruit_NeoPixel ring(RING_COUNT, RING_PIN, NEO_GRB + NEO_KHZ800);        // declare NP ring see below for details
Adafruit_NeoPixel strip(STRIP_COUNT, STRIP_PIN, NEO_GRB + NEO_KHZ800);  // declare NP strand see below for details
// Future Referece:
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)



void setup() {

  Serial.begin(9600);                   // Starting the serial monitor
  CircuitPlayground.begin();            // Initiating the Circuit Playground
  pinMode(CACTUS_PIN, INPUT_PULLUP);    // Indicating the type of input for the pin used **look into this more
  pinMode(SKATE_PIN, INPUT_PULLUP);     // Indicating the type of input for the pin used

  pinMode(RING_PIN, INPUT_PULLUP);      // Indicating the type of input for the pin used
  pinMode(STRIP_PIN, INPUT_PULLUP);      // Indicating the type of input for the pin used


  ring.begin();              // INITIALIZE NeoPixel strip object (REQUIRED)
  ring.show();               // Turn OFF all pixels ASAP
  ring.setBrightness(50);    // Set BRIGHTNESS to about 1/5 (max = 255)

  strip.begin();             // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();              // Turn OFF all pixels ASAP
  strip.setBrightness(50);   // Set BRIGHTNESS to about 1/5 (max = 255)
}


void loop() {
  cactusVal = digitalRead(CACTUS_PIN);    // Reading the current value of the button pin (is it activated or not?)
  skateVal = digitalRead(SKATE_PIN);      // Reading the current value of the button pin (is it activated or not?)
  Serial.println(cactusVal);
  Serial.println(skateVal);

  //Rings
  if (cactusVal == LOW) { // if the digital switch is activated
    for (int i = 0 ; i < ring.numPixels(); i++) { // loop through all of the LED lights on the NeoPixels and light them up.
      ring.setPixelColor(i, 0, 255, 0); // Green Colour
      ring.show();
    }
  } else { // if the digital switch is not activated, turn the LED lights off.
    ring.clear();
    ring.show();
  }
  if (skateVal == LOW) { // if the digital switch is activated
    for (int i = 0 ; i < ring.numPixels(); i++) { // loop through all of the LED lights on the NeoPixels and light them up.
      ring.setPixelColor(i, 255, 0, 0); // Red Colour
      ring.show();
    }
  } else { // if the digital switch is not activated, turn the LED lights off.
    ring.clear();
    ring.show();
  }

// Strand & Possible Animation
  if (cactusVal == LOW) { // if the digital switch is activated
    //rainbow = !rainbow;
    for (int i = 0 ; i < strip.numPixels(); i++) { // loop through all of the LED lights on the NeoPixels and light them up.
      strip.setPixelColor(i, 0, 255, 0); // Green Colour
      strip.show();
    }
  } else { // if the digital switch is not activated, turn the LED lights off.
    strip.clear();
    //rainbow(10);             // Flowing rainbow cycle along the whole strip                     
    strip.show();
  }

  if (skateVal == LOW) { // if the digital switch is activated
    //rainbow = !rainbow;
    for (int i = 0 ; i < strip.numPixels(); i++) { // loop through all of the LED lights on the NeoPixels and light them up.
      strip.setPixelColor(i, 255, 0, 0); // Red Colour
      strip.show();
    }
  } else { // if the digital switch is not activated, turn the LED lights off.
    strip.clear(); 
    //rainbow(10);             // Flowing rainbow cycle along the whole strip             
    strip.show();
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
