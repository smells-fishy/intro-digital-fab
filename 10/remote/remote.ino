void setup() {
  //Set up input pins
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  //Set up the monitor to print
  Serial.begin(9600);
}

void loop() {

  //Read pin 2 and output
  Serial.println(digitalRead(2));

  //Read pin 4 and output
  //Serial.println(digitalRead(4));

}
