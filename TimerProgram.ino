#include <Adafruit_CircuitPlayground.h>

//ITERATION 1: Left external button sets timer variable, right internal turns timer on & resets timer, RIGHT BUTTON press and hold for complete reset

int pushButtonRight; //creates two variables for each pushbutton 
int pushButtonLeft;
int timer = 0; //creates a timer variable

void setup() {
  Serial.begin(9600); 
  CircuitPlayground.begin();
  pinMode(0, INPUT);
  pinMode(6, INPUT);
}

void loop() {
  //Setting the timer variable
  pushButtonLeft = digitalRead(6); //checks and writes the state of the left button
  if(pushButtonLeft) {
    delay(500); //brief buffer pause
    timer += 1000; //increases the timer by the timer interval (currently 10 minutes)
    CircuitPlayground.setPixelColor((timer/1000)-1, 255, 255, 255); //lights up one more LED
    if(timer>10000) {

      
      timer=0; //resets the timer once it reaches the maximum (currently 10 seconds)
      CircuitPlayground.clearPixels(); //resets all LEDS
    }
  }
  
  //Running the timer (press) or resetting completely (press and hold)
  pushButtonRight = digitalRead(0); //checks and writes the state of the right button
  if(pushButtonRight) {
    for(int y=0; y<=3000; y+=100) { //loops until 5 seconds have passed, in intervals of 100 milliseconds
      pushButtonRight = digitalRead(0); //checks and writes the state of the right button
      delay(100); //wait 100 milliseconds
      if(!(pushButtonRight) && timer>0) { //checks to see if the right button has been released
        y=0; //resets y, so that it doesn't have the same value the next time the right button is pressed
        for(int x=(timer/1000)-1; x>=0; x--) {
          delay(1000); //waits for one timer interval
          CircuitPlayground.setPixelColor(x, 255, 0, 0); //turns one LED red, as the timer intervals go down
        }
        //Timer ringing
        pushButtonRight = digitalRead(0); //checks and writes the state of the right button
        while(!(pushButtonRight)) {  //loops through the alarm tone, checking to see if the OFF button is pressed
          CircuitPlayground.playTone(261.626, 100); //plays beep alarm tone for 1/10 of a second
          pushButtonRight = digitalRead(0); //checks and writes the state of the right button
        }
        for(int i=0; i<= (timer/1000)-1; i++) {
          CircuitPlayground.setPixelColor(i, 255, 255, 255); //turns all of the red countdown LEDs white again, showing the timer is restarted
        }
      }
    }
      timer=0; //after 5 seconds, if the button was not released, resets timer variable
      CircuitPlayground.clearPixels(); //resets LEDs
  }
}
