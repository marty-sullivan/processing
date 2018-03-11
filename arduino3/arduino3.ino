int robot_pin = 9;
int buzzer_pin = 10;

int red_pin = 11;
int yellow_pin = 12;
int green_pin = 13;

int button = 0;
int crank = 0;
int voice = 0;
int robot;
float hit_counter = 0;

int button_count = 0;
boolean button_State;

int voice_count = 0;
boolean voice_State;

int ledState; 
long previousMillis; 
long interval = 1000;

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
      button_State = true;
    }
  } 
  else {
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
  } 
  else {
    voice_State = false;
  }

  if (voice_count > 255) {
    voice_count = 255;
  }

  if (voice_count < 1 ) {
    voice_count = 0;
  }



  robot = button_count + crank/4 + voice_count;
  ;


  if (robot>255) {
    robot = 255;
  } 

  if (robot>150) {
    hit_counter = hit_counter + 3;  
  }


  hit_counter = hit_counter - 2;

  if (hit_counter < 1) {
    hit_counter = 0;
  }
  
  if (hit_counter <50) {
   for(int i=10;i<14;i++) {
    digitalWrite(i,LOW);
   }
  }
  
  if (hit_counter>50 && hit_counter<300) {
    blinking(11,300);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
  }
  
  if (hit_counter>300 && hit_counter<600) { 
    digitalWrite(11,HIGH);
    blinking(12,300);
    digitalWrite(13,LOW);  
  }
  
  if (hit_counter>600 && hit_counter<900) { 
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    blinking(13,300); 
  } 
  
  if (hit_counter >900) {
    hit_counter = 0;
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    delay(3000);
  }  


  analogWrite(robot_pin,robot);
  


  Serial.println(hit_counter);

}

void blinking(int pin, long time) {
  int ledPin = pin;
  interval = time;
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



