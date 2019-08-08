#include <SPI.h>
#include "RF24.h"

//Radio setup
RF24 radio(7, 8);

byte addresses[][6] = {"Remo", "Fan"};


//Speed button feedback
byte spdUpButton;
byte spdDownButton;

//Directional control
byte upButton;
byte downButton;
byte leftButton;
byte rightButton;

byte info;

void setup() {
  //Set up speed control button input pins
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  //Set up motor control button input pins
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(9, INPUT);

  //Serial monitor initialization for debugging
  Serial.begin(115200);

  //Initialize radio object
  radio.begin();

  // Set the PA Level low to prevent power supply related issues
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

}

void loop() {

  //Speed button feedback
  spdUpButton = digitalRead(6);
  spdDownButton = digitalRead(9);

  //Directional control
  upButton = digitalRead(4);
  downButton = digitalRead(2);
  leftButton = digitalRead(5);
  rightButton = digitalRead(3);

  if (spdUpButton == HIGH) {
    info = 2;
    if (!radio.write(&info, 1)) {
    Serial.println("failed spd up");
    } radio.write(&info, 1);
  }
  else if (spdDownButton == HIGH) {
    info = 1;
    if (!radio.write(&info, 1)) {
    Serial.println("failed spd down");
    } radio.write(&info, 1);
  }
  else if (upButton == HIGH && leftButton == LOW && rightButton == LOW) {
    info = 2;
    if (!radio.write(&info, 1)) {
    Serial.println("failed ud up");
    } radio.write(&info, 1);
  }
  else if (downButton == HIGH && leftButton == LOW && rightButton == LOW) {
    info = 1;
    if (!radio.write(&info, 1)) {
    Serial.println("failed ud down");
    } radio.write(&info, 1);
  }
  else if (rightButton == HIGH) {
    info = 2;
    if (!radio.write(&info, 1)) {
    Serial.println("failed lr right");
    } radio.write(&info, 1);
  }
  else if (leftButton == HIGH) {
    info = 1;
    if (!radio.write(&info, 1)) {
    Serial.println("failed lr left");
    } radio.write(&info, 1);
  }
}
