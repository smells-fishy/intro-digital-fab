int var = 0;
int sum = 0;
int N_samples = 1000;

void setup() {
  Serial.begin(9600);
}
void loop() {
  var = analogRead(A0);
  /*if(var >= 1){
    var = constrain(var, 1, 100);                        
    var = map(var, 1, 100, 1, 255);
    analogWrite(11, var);
   }else{
       analogWrite(11, 0);                     
  }*/
  unsigned long int sum = 0;

 /*for (int i = 0; i < N_samples; i++){        //Measure response of conductor 2.
   sum += var;                       //Sums up N_samples of these measurements.
 }*/
 Serial.println(var);
 //delay(1000/10); //Aliasing effect feature
}
