#include <Adafruit_CircuitPlayground.h>

//ITERATION 0: Left button sets timer value, right button turns timer on & resets the timer once it runs out, no off button

bool pushButtonRight; //creates two booleans for each pushbutton 
bool pushButtonLeft;
int timer = 0;

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  //Setting the timer
  pushButtonLeft = CircuitPlayground.leftButton(); //checks and writes the state of the left button
  if(pushButtonLeft) {
    delay(500); //brief buffer pause (500 milliseconds)
    timer += 1000; //increases the timer by the timer interval (currently 1 second for test purposes)
    CircuitPlayground.setPixelColor((timer/1000)-1, 255, 255, 255); //lights up one more LED
    if(timer>10000) {
      timer=0; //resets the timer once it reaches the maximum (currently 10 seconds)
      CircuitPlayground.clearPixels(); //resets all LEDS
    }
  }

  if(timer>0 && pushButtonRight) {
    for(int x=(timer/1000)-1; x>=0; x--) {
      delay(1000); //waits for one timer interval
      CircuitPlayground.setPixelColor(x, 255, 0, 0); //turns one LED red, going in the opposite direction as the timer was set
    }
    //Timer ringing
    pushButtonRight = CircuitPlayground.rightButton(); //checks and writes the state of the right button
    while(!(pushButtonRight)) {  //loops through the alarm tone, checking to see if the OFF button is pressed
      CircuitPlayground.playTone(261.626, 100); //plays beep alarm tone for 1/10 of a second
      pushButtonRight = CircuitPlayground.rightButton(); //checks and writes the state of the right button
    }
    for(int i=0; i<= (timer/1000)-1; i++) {
      CircuitPlayground.setPixelColor(i, 255, 255, 255);
    }
  }
}
