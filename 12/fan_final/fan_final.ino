#include <SPI.h>
#include "RF24.h"

//Sets up radio on SPI bus and pin 7&8
RF24 radio(7,8);

byte addresses[][6] = {"Remo","Fan"};

//Individual data to array
byte data1;

//Data array
byte data[3];

//Initial speed value
float output = 25.5 * 5;

//Pins for motor control
int leftA = 2;
int leftB = 3;
int rightA;
int rightB;

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 3; i++){
    radio.read(&data1, 1);
    data[i] = data1;
    Serial.print(data1);
  }

  //Speed down-modulation code
  if(data[0] == 1) {
    //Ensure speed doesn't go below 0
    if (output > 0){
      output -= 25.5;
    } else {}
  }

  //Speed up-modulation code
  else if(data[0] == 2) {
    //Ensure speed doesn't go above 255
    if (output < 255){
      output += 25.5;
    } else{}
  }
  
  //Go forward
  else if(data[1] == 1) {
     digitalWrite(leftA, HIGH);
     digitalWrite(leftB, LOW);
     digitalWrite(rightA, HIGH);
     digitalWrite(rightB, LOW);
  }

  //Go backward
  else if(data[1] == 2) {
    digitalWrite(leftA, LOW);
    digitalWrite(leftB, HIGH);
    digitalWrite(rightA, LOW);
    digitalWrite(rightB, HIGH);
  }

  //Turn left (left backward, right forward)
  else if(data[2] == 1) {
     digitalWrite(leftA, LOW);
     digitalWrite(leftB, HIGH);
     digitalWrite(rightA, HIGH);
     digitalWrite(rightB, LOW);
  }

  //Turn right (left forward, right backward)
  else if(data[2] == 2) {
    digitalWrite(leftA, LOW);
    digitalWrite(leftB, HIGH);
    digitalWrite(rightA, LOW);
    digitalWrite(rightB, HIGH);
  }
}
