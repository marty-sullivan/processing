int button = 0;
int crank = 0;
int voice = 0;
int robot;

int button_count = 0;
boolean button_State;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  /*
    digitalWrite(11,HIGH);
    delay(10000);

    digitalWrite(11,LOW);
    delay(10000);
  */
  crank = analogRead(0);
  button = analogRead(1);
  voice = analogRead(2);

  

  Serial.println(button_co


}
