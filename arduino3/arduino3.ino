int robot_pin = 9;
int buzzer_pin = 10;
int red_pin = 11;
int yellow_pin = 12;
int green_pin = 13;

int button = 0;
int crank = 0;
int voice = 0;
int robot;
int hit_counter = 0;

int button_count = 0;
boolean button_State;

int voice_count = 0;
boolean voice_State;

void setup() {
  // put your setup code here, to run once:
  for(int i=9;i<14;i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  crank = analogRead(0);
  button = analogRead(1);
  voice = analogRead(2);
  
  //button_control
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
  
  //voice control
  voice_count = int(voice_count - 0.1);

  if (voice > 700) {
    if (!button_State) {
      voice_count = voice_count + 255 ;
      voice_State = true;
    }
  } else {
    voice_State = false;
  }

  if (voice_count > 255) {
    voice_count = 255;
  }

  if (voice_count < 1 ) {
    voice_count = 0;
  }


 
  robot = button_count + crank/4 + voice_count;;


  if (robot>255) {
    robot = 255;
    hit_counter++;
  } 
  
  //hit_counter = int(hit_counter - 0.001);
  

  
  analogWrite(robot_pin,robot);
  

  Serial.println(robot);

}

void blinking(int pin, int time) {
  int ledPin = pin;
  int interval = time;
  int ledState; 
  long previousMillis; 
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
  
}


