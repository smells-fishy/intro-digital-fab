int aPinA = 2;
int aPinB = 3;

void setup() {
  //Initialize pins needed for motor driving
  pinMode(aPinA, OUTPUT);
  pinMode(aPinB, OUTPUT);
}

void loop() {
  //Run counter-clockwise
  digitalWrite(aPinA, HIGH);
  digitalWrite(aPinB, LOW);

  //Wait for a second
  delay(1000);

  //Switch directions/polarity and run clockwise
  digitalWrite(aPinA, LOW);
  digitalWrite(aPinB, HIGH);

  delay(1000);
}
