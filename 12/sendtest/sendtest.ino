#include <SPI.h>
#include "RF24.h"

//Sets up radio on SPI bus and pin 7&8
RF24 radio(7,8);

byte addresses[][6] = {"Remo","Fan"};

//Radio Input variable
byte feedback = 1;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!radio.write(&feedback, 1)){
    Serial.println("Failed");
  }radio.write(&feedback, 1);
  
}
