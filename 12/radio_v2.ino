#include <SPI.h>
#include "RF24.h"

//Radio setup
RF24 radio(7,8);

byte addresses[][6] = {"Remo","Fan"};


//Button feedback
byte spdUpButton;
byte spdDownButton;

byte upButton;
byte downButton;
byte leftButton;
byte rightButton;

void setup() {
  //Set up speed control button input pins
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  //Set up motor control button input pins
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  //Serial monitor initialization for debugging
  Serial.begin(115200);

  //Initialize radio object
  radio.begin();

  // Set the PA Level low to prevent power supply related issues
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
  
}

void loop() {

  //Read speed control buttons
  spdUpButton = digitalRead(2);
  spdDownButton = digitalRead(3);

  //Data to be sent
  byte feedback = 0;

  //Code for data transmission for speed modulation
  if(spdUpButton == HIGH) {                  //If the speed up button is pressed, increment the fan speed up
    feedback = 1;
    if(!radio.write(&feedback, 1)){
      Serial.println("failed");
    }
    radio.write(&feedback, 1);
  } else if(spdDownButton == HIGH) {         //If the speed down button is pressed, increment the fan speed down
    feedback = 0;
    if(!radio.write(&feedback, 1)){
      Serial.println("failed");
    }
    radio.write(&feedback, 1);
  } else { }                                 //Alternatively, do nothing

  //Read the d-pad buttons
  upButton = digitalRead(4);
  downButton = digitalRead(5);
  leftButton = digitalRead(6);
  rightButton = digitalRead(7);

  //Data to be sent
  byte udFeed;
  byte lrFeed;

  //Code for data transmission for up/down direction
  if(upButton == HIGH && downButton == LOW && rightButton == LOW) {                  //If the up button is pressed, drive forward, but only if turning is not active
    udFeed = 1;
    if(!radio.write(&udFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&udFeed, 1);
  } else if(downButton == HIGH && downButton == LOW && rightButton == LOW) {         //If the down button is pressed, drive backwards, but only if turning is not active
    udFeed = 0;
    if(!radio.write(&udFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&udFeed, 1);
  } else { }                                 //Alternatively, do nothing

  //Code for data transmission for left/right direction
  if(leftButton == HIGH) {                  //If the left button is pressed, turn to the left
    lrFeed = 0;
    if(!radio.write(&lrFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&udFeed, 1);
  } else if(rightButton == HIGH) {         //If the right button is pressed, turn to the right
    lrFeed = 1;
    if(!radio.write(&lrFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&udFeed, 1);
  } else { }                                 //Alternatively, do nothing
  
}
