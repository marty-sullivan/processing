int button = 0;
int crank = 0;
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

  
  button_count = int(button_count - 0.1);

  if (button > 1000) {
    if (!button_State) {
      button_count = button_count + 255 ;
      Serial.println("pressed");
      button_State = true;
    }
  } else {
    button_State = false;
  }

  if (button_count > 255) {
    button_count = 255;
  }

  if (button_count < 1 ) {
    button_count = 0;
  }

  robot = button_count + crank/4;

  if (robot>255) {

    robot = 255;
  }

  
  analogWrite(11,robot);
  

  Serial.println(button_count);



}
