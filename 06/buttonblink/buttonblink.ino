void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT); //button
  pinMode(3, OUTPUT);

  //Debug options
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte buttonState = digitalRead(2);
  
  
  //Debug
  //unsigned int volt = analogRead(A0);
  Serial.println(buttonState);
  //Serial.println(volt);
  
  if(buttonState == HIGH){
  Serial.println("if'd");
  for (int i = 10; i > 0; i--){
      Serial.println("looped");
      analogWrite(3, i*25.5);
      delay(1000);
    }
  } else {}
}
