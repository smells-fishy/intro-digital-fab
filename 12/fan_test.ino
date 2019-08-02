void setup() {
  //Set up pins for wire data reading
  //6 is connected to blue
  //A0 is connected to green
  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);

  //Initialize serial monitor to observe data.
  Serial.begin(9600);
}

void loop() {
  //Write a value of 1 out of 255 
  //to PWM pin 6 in order to see if the blue wire is speed signal
  analogWrite(6, 1);

  //Read from green wire to see if it's the output
  int output = analogRead(A0);
  Serial.println(output);
}
