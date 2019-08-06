#include <SPI.h>
#include "RF24.h"

//Radio setup
RF24 radio(7,8);

byte addresses[][6] = {"Remo","Fan"};


//Speed button feedback
byte spdUpButton;
byte spdDownButton;

//Directional control
byte upButton;
byte downButton;
byte leftButton;
byte rightButton;

//Radio feedback
byte info;
byte feedback = 0;

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
  //Send byte to indicate that the next byte controls up/down, then wait
  info = 0;
  if(!radio.write(&info, 1)){
      Serial.println("failed");
    }
  radio.write(&info, 1);
  wait();
  
  //Read speed control buttons
  spdUpButton = digitalRead(2);
  spdDownButton = digitalRead(3);

  //Data to be sent
  byte spdFeed = 0;

  //Code for data transmission for speed modulation
  if(spdUpButton == HIGH) {                  //If the speed up button is pressed, increment the fan speed up
    spdFeed = 1;
    if(!radio.write(&spdFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&spdFeed, 1);
  } else if(spdDownButton == HIGH) {         //If the speed down button is pressed, increment the fan speed down
    spdFeed = 0;
    if(!radio.write(&spdFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&spdFeed, 1);
  } else {                                   //Alternatively, do nothing
    spdFeed = 14;
    if(!radio.write(&spdFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&spdFeed, 1);
  }
  
  //Start listening for feedback from fan
  wait();

  //Send byte to indicate that the next byte controls up/down, then wait
  info = 1;
  if(!radio.write(&info, 1)){
      Serial.println("failed");
    }
  radio.write(&info, 1);
  wait();
  
  //Read the d-pad buttons
  upButton = digitalRead(4);
  downButton = digitalRead(5);
  leftButton = digitalRead(6);
  rightButton = digitalRead(7);

  //Data to be sent
  byte udFeed;
  byte lrFeed;

  //Code for data transmission for up/down direction
  if(upButton == HIGH && leftButton == LOW && rightButton == LOW) {                  //If the up button is pressed, drive forward, but only if turning is not active
    udFeed = 0;
    if(!radio.write(&udFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&udFeed, 1);
  } else if(downButton == HIGH && leftButton == LOW && rightButton == LOW) {         //If the down button is pressed, drive backwards, but only if turning is not active
    udFeed = 1;
    if(!radio.write(&udFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&udFeed, 1);
  } else {                                                                           //Alternatively, do nothing
    udFeed = 14;
    if(!radio.write(&udFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&udFeed, 1);
  }
  
  //Start listening for feedback from fan
  wait();

  //Send byte to indicate that the next byte controls up/down, then wait.
  info = 2;
  if(!radio.write(&info, 1)){
      Serial.println("failed");
    }
  radio.write(&info, 1);
  wait();
  
  //Code for data transmission for left/right direction
  if(leftButton == HIGH) {                  //If the left button is pressed, turn to the left
    lrFeed = 0;
    if(!radio.write(&lrFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&lrFeed, 1);
  } else if(rightButton == HIGH) {         //If the right button is pressed, turn to the right
    lrFeed = 1;
    if(!radio.write(&lrFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&lrFeed, 1);
  } else {                                 //Alternatively, do nothing
    lrFeed = 14;
    if(!radio.write(&lrFeed, 1)){
      Serial.println("failed");
    }
    radio.write(&lrFeed, 1);
  }
  
  //Start listening for feedback from fan
  wait();
  
}

void wait() {
  //Let the radio listen
  
  radio.startListening();
  while(feedback == 0) {
    if(radio.available()){
      radio.read(&feedback, 1);
    }
  }
  Serial.println("Response received");
  feedback = 0;
  radio.stopListening();
}
