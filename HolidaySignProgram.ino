#include <Adafruit_CircuitPlayground.h>

bool pushButtonRight;
bool pushButtonLeft;

void setup() {
  CircuitPlayground.begin();
}

void pixelsStartUpShutDown(int R, int G, int B, int waitTime, bool descending) {
  double ScalePitches[] = {130.813, 146.832, 164.814, 174.614, 195.998, 220, 246.942, 261.626}; //makes an array with the notes of the middle C major scale
  double ScalePitchesDescending[] = {261.626, 246.942, 220, 195.998, 174.614, 164.814, 146.832, 130.813};
  for(int i=0; i<=9; i++){ //loops through all 9 neopixels
    if(descending) { //if it is descending (the closing sequence) the lights blink off, scale goes down
      CircuitPlayground.setPixelColor(i, 0, 0, 0); //sets neopixel at position i to the given RGB sequence
      if(i>=1 && i<=8) {
        CircuitPlayground.playTone(ScalePitchesDescending[i-1],100);    // output a 440 Hz sound for a tenth of a second
      }
      delay(waitTime);
    }
    else {
      CircuitPlayground.setPixelColor(i, R, G, B); //sets neopixel at position i to the given RGB sequence
      if(i>=1 && i<=8) {
        CircuitPlayground.playTone(ScalePitches[i-1],100);    // output a 440 Hz sound for a tenth of a second
      }
      delay(waitTime);
    }
  }
}

void pixelsBlink(int R, int G, int B, int onTime, int offTime) {
  CircuitPlayground.clearPixels(); //turn pixels off
  delay(offTime); //blink LEDs off for given off time
  for(int i=0; i<=9; i++) { //loops through all 9 neopixels
    CircuitPlayground.setPixelColor(i, R, G, B); //sets neopixel at position i to the given RGB sequence
  }
  delay(onTime); //keep LEDs on for given on time
}

void loop() {
  pushButtonRight = CircuitPlayground.rightButton();
  pushButtonLeft = CircuitPlayground.leftButton();
  if(pushButtonLeft) { //checks if the left button is pressed
    pixelsStartUpShutDown(255, 255, 255, 500, false); //runs the "start up" light sequence
    while(!(pushButtonRight = CircuitPlayground.rightButton())) {
      pixelsBlink(255, 255, 255, 1200, 400); //loops the blink sequence while the right button is not pressed
    }
  }
  if(pushButtonRight) { //checks if the right button is pressed
    pixelsStartUpShutDown(0,0,0, 500, true); //runs the shut down light/sound sequence
  }
}
