#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#define CHIP_SELECT 4

#define NUM_TWEETS 4
#define TEXT_SIZE 4

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

String tweet;
int x, min_x, max_x;
int current_tweet = 0;

File tweets_file;

String read_tweet() {
  String tweet = "";

  if (!tweets_file.available()) {
    Serial.println("\n\nEND FILE\n\n");
    delay(2000);
    tweets_file.close();
    tweets_file = SD.open("tweets.csv");
  }
  
  while (true) {
    char c = tweets_file.read();
    
    if (c == '"') 
      continue;
    else if (c == '\n')
      break;

    tweet += c;
  }

  return tweet;
}

void setup() {
  Serial.begin(9600);
  
  Serial.print("Initializing SD Card...");
  SD.begin(CHIP_SELECT);
  tweets_file = SD.open("tweets.csv");
  tweet = read_tweet();

  Serial.print("Initializing Display...");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.setTextSize(TEXT_SIZE);
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  x = display.width();
  
  display.clearDisplay();
  delay(1);
}

void loop() {    
  x -= 4;
  
  if (x < min_x) { 
    tweet = read_tweet();
    x = max_x;
    min_x = -6 * TEXT_SIZE * tweet.length();
    max_x = min_x * -1;

    Serial.println(tweet);
  }
  
  display.clearDisplay();
  display.setCursor(x, 0);
  display.print(tweet);
  display.display();
}
