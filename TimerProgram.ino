#include <Adafruit_CircuitPlayground.h>

//ITERATION 1: Left sets timer variable, right turns timer on & resets timer, RIGHT BUTTON press and hold for complete reset

bool pushButtonRight; //creates two booleans for each pushbutton 
bool pushButtonLeft;
int timer = 0; //creates a timer variable

void setup() {
  CircuitPlayground.begin();
}

void runTimer() {
  Serial.print("got here! ");
  for(int x=(timer/600000)-1; x>=0; x--) {
    delay(600000); //waits for one timer interval
    CircuitPlayground.setPixelColor(x, 255, 0, 0); //turns one LED red, as the timer intervals go down
  }
  //Timer ringing
  pushButtonRight = CircuitPlayground.rightButton(); //checks and writes the state of the right button
  while(!(pushButtonRight)) {  //loops through the alarm tone, checking to see if the OFF button is pressed
    CircuitPlayground.playTone(261.626, 100); //plays beep alarm tone for 1/10 of a second
    pushButtonRight = CircuitPlayground.rightButton(); //checks and writes the state of the right button
  }
  for(int i=0; i<= (timer/600000)-1; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255); //turns all of the red countdown LEDs white again, showing the timer is restarted
  }
}

void loop() {
  //Setting the timer variable
  pushButtonLeft = CircuitPlayground.leftButton(); //checks and writes the state of the left button
  if(pushButtonLeft) {
    delay(500); //brief buffer pause
    timer += 600000; //increases the timer by the timer interval (currently 10 minutes)
    CircuitPlayground.setPixelColor((timer/600000)-1, 255, 255, 255); //lights up one more LED
    if(timer>6000000) {
      timer=0; //resets the timer once it reaches the maximum (currently 100 minutes )
      CircuitPlayground.clearPixels(); //resets all LEDS
    }
  }
  
  //Running the timer (press) or resetting completely (press and hold)
  pushButtonRight = CircuitPlayground.rightButton(); //checks and writes the state of the right button
  if(pushButtonRight) {
    for(int y=0; y<=5000; y+=100) { //loops until 5 seconds have passed, in intervals of 100 milliseconds
      pushButtonRight = CircuitPlayground.rightButton(); //checks and writes the state of the right button
      delay(100); //wait 100 milliseconds
      if(!(pushButtonRight) && timer>0) { //checks to see if the right button has been released
        runTimer(); //runs the timer procedure
      }
    }
      timer=0; //after 5 seconds, if the button was not released, resets timer variable
      CircuitPlayground.clearPixels(); //resets LEDs
  }
}
