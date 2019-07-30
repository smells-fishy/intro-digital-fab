void setup() {
  // Set up input/output pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(6, OUTPUT);

  //Initialize serial monitor to observe data.
  Serial.begin(9600);
}

void loop() {
  //Take in a number from 0 to 1023
  int input = analogRead(A1);

  //Map input to 0 to 255 in order to allow PWM output
  input = map(input, 0, 1023, 0, 255);
  
  //Output data and write to fan 
  Serial.println(input);
  analogWrite(6, input);

  //Optional debug code
  //int output = analogRead(A0);
  //Serial.println(output);
}
