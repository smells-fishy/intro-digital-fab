#include <SPI.h>
#include "RF24.h"

//Sets up radio on SPI bus and pin 7&8
RF24 radio(7,8);

byte addresses[][6] = {"Remo","Fan"};

//Radio Input variable
byte feedback;

void setup() {
  // Set up input/output pins
  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);

  //Initialize serial monitor to observe data.
  Serial.begin(115200);
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() {
  //Put out a middle value from 0 to 255
  float output = 25.5 * 5;


  //Check if there are available bytes to read, and then receive
  if(radio.available()){
    radio.read( &feedback, 1);
  }
  //Serial.println(feedback);

  //Speed down-modulation code
  if(feedback == 0) {
    //Ensure speed doesn't go below 0
    if (output > 0){
      output -= 25.5;
    } else {}
  }

  //Speed up-modulation code
  else if(feedback == 1) {
    //Ensure speed doesn't go above 255
    if (output < 255){
      output += 25.5;
    } else{}
  }

  //Set feedback variable to 2 to allow for discrete signal reading
  feedback = 2;
  
  analogWrite(6, output);
  Serial.println(output);
  
  //Optional debug code
  //int output = analogRead(A0);
  //Serial.println(output);
}
