int aPinA = 2;
int aPinB = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(aPinA, OUTPUT);
  pinMode(aPinB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(aPinA, HIGH);
  digitalWrite(aPinB, LOW);

  delay(1000);

  digitalWrite(aPinA, LOW);
  digitalWrite(aPinB, HIGH);
}
