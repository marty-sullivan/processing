int button = 0;
int crank = 0;
int voice = 0;

int robot;

int button_count = 0;
boolean button_State;

int voice_count = 0;
boolean voice_State;


void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
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






  //robot = voice_count;
  

  robot = button_count + crank/4 + voice_count;;

  
  //Serial.println(voice);
  //robot = voice;


  if (robot>255) {
    robot = 255;
  }

  
  analogWrite(11,robot);
  

  Serial.println(voice_count);



}
