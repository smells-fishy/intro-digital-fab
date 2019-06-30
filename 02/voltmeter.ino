void setup() {
  // put your setup code here, to run once:
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int voltage = analogRead(A1);
  Serial.println(voltage);
  delay(10);
}
