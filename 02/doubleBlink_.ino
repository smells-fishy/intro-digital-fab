const int loopTime1 = 500;
const int loopTime2 = 1000;

byte led1State = LOW;
byte led2State = LOW;

unsigned long currentMillis = 0;
unsigned long previousOn1 = 0;
unsigned long previousOn2 = 0;
unsigned long onTime1 = 1000;
unsigned long onTime2 = 2000;


void setup() {
  // put your setup code here, to run once:
  pinMode (1, OUTPUT);
  pinMode (2, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
 currentMillis = millis();
 updateLed1();
 updateLed2();
 updateBoard();

}

void updateLed1() {
  if (led1State == LOW && currentMillis - previousOn1 >= onTime1) {
      
      led1State = HIGH;
      previousOn1 += onTime1;
 
   } else if (currentMillis - previousOn1 >= loopTime1) {

     led1State = LOW;
    
   }

}

void updateLed2() {
  if (led2State == LOW && currentMillis - previousOn2 >= onTime2) {
      
      led2State = HIGH;
      previousOn2 += onTime2;

   } else if (currentMillis - previousOn2 >= loopTime2) {

     led2State = LOW;
    
   }
}

void updateBoard(){

  digitalWrite(1, led1State);
  digitalWrite(2, led2State);

}
