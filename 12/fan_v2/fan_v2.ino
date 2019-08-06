#include <SPI.h>
#include "RF24.h"

//Sets up radio on SPI bus and pin 7&8
RF24 radio(7,8);

byte addresses[][6] = {"Remo","Fan"};

//Radio infotype variable
byte info = 0;

//Radio Speed Input variable
byte feedback;


//Radio For/Backward control
byte udfeed;

//Radio left/right control
byte lrfeed;

//Radio respond
byte respondc = 1;

//Pins for motor control
int leftA;
int leftB;
int rightA;
int rightB;

//Initial speed value
float output = 25.5 * 5;

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
  while(info == 0) {
    if(radio.available()){
      radio.read(&info, 1);
    }
  }
  respond();
  
  if(info == 11){
    spd();
    respond();
  }
  
  else if(info==12){
    ud();
    respond();
  }
  
  else if(info==13){
    lr();
    respond();
  }

  info = 0;
}

void respond() {
  radio.stopListening();
  if(!radio.write(&respondc, 1)){
    Serial.println("Failed");
  } radio.write(&respondc, 1);
  Serial.println("Response Sent");
  radio.startListening();
}

void spd() {

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
  feedback = 10;

  //Update fan speed
  analogWrite(6, output);
  Serial.println(output);
  
}

void ud() {

  if(radio.available()){
    radio.read( &udfeed, 1);
  }

  //Go forward
  if(udfeed == 0) {
     digitalWrite(leftA, HIGH);
     digitalWrite(leftB, LOW);
     digitalWrite(rightA, HIGH);
     digitalWrite(rightB, LOW);
  }

  //Go backward
  else if(udfeed == 1) {
    digitalWrite(leftA, LOW);
    digitalWrite(leftB, HIGH);
    digitalWrite(rightA, LOW);
    digitalWrite(rightB, HIGH);
  }

 Serial.println(udfeed);
 udfeed = 10;
}

void lr() {

  if(radio.available()){
    radio.read( &lrfeed, 1);
  }

  //Turn left (left backward, right forward)
  if(lrfeed == 0) {
     digitalWrite(leftA, LOW);
     digitalWrite(leftB, HIGH);
     digitalWrite(rightA, HIGH);
     digitalWrite(rightB, LOW);
  }

  //Turn right (left forward, right backward)
  else if(lrfeed == 1) {
    digitalWrite(leftA, LOW);
    digitalWrite(leftB, HIGH);
    digitalWrite(rightA, LOW);
    digitalWrite(rightB, HIGH);
  }

  Serial.println(lrfeed);
  lrfeed = 10;
}
