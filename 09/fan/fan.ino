#include <SPI.h>
#include "RF24.h"

bool radioNumber = 0;

//Sets up radio on SPI bus and pin 7&8
RF24 radio(7,8);

byte addresses[][6] = {"1Node","2Node"};

//Indicates that this node is receiving
bool role = 0;

//Radio Input variable
int feedback;

void setup() {
  // Set up input/output pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(6, OUTPUT);

  //Initialize serial monitor to observe data.
  Serial.begin(115200);
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() {
  //Take in a number from 0 to 1023
  int input = analogRead(A1);
  int radio = radio.read(&feedback, sizeof(feedback));
  
  //Map input to 0 to 255 in order to allow PWM output
  input = map(input, 0, 1023, 0, 255);
  
  //Output data and write to fan 
  Serial.println(input);
  analogWrite(6, input);
  
  //Optional debug code
  //int output = analogRead(A0);
  //Serial.println(output);
}
