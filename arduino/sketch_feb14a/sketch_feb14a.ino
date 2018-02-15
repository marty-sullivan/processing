int crank = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(11,OUTPUT);
  Serial.begin(9600);
}

void loop() {
/*
  digitalWrite(11,HIGH);
  delay(10000);
 
  digitalWrite(11,LOW);
  delay(10000);
*/

  crank = analogRead(1);
  Serial.println(crank);
  analogWrite(11,crank/4); 
  
  
}
