#include <SPI.h>
#include "RF24.h"

//Radio setup
RF24 radio(7,8);

byte addresses[][6] = {"Remo","Fan"};


//Button feedback
byte upButton;
byte downButton;

void setup() {
  //Set up speed control button input pins
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  //Set up motor control button input pins
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  
  Serial.begin(115200);
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  
}

void loop() {

  upButton = digitalRead(2);
  downButton = digitalRead(4);

  

  //Serial.println(upButton);

  byte feedback = 0;

  if(upButton == HIGH) {
    feedback = 1;
    if(!radio.write(&feedback, 1)){
      Serial.println("failed");
    }
    radio.write(&feedback, 1);
  } else if(downButton == HIGH) {
    feedback = 0;
    if(!radio.write(&feedback, 1)){
      Serial.println("failed");
    }
    radio.write(&feedback, 1);
  } else { }
}
