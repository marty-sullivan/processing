/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
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

#define NUM_TWEETS 4
#define TEXT_SIZE 3

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

const char tweets[][64] PROGMEM = {
"i have to go…",
"i have to Love God More Deeply",
"i have to slap people who use this phrase",
"i have to sleep fuckin sleep man",
"i have to rip my heart out",
"i have to teach i should give up what i love.",
"i have to win a #bouclair gift card @MsAmandaForrest!",
"i have to get with someone i always propose we watch a scary movie so that i can act ‘scared’ and i.",
"i have to travel with two things in my hands- A camera in one hand and yours in the other ",
"i have to suck your fingers clean, and suck your tits",
"i have to say that to Momo too!",
"i have to do that too.",
"i have to go to the Cheesecake Factory on Valentine’s Day lol.",
"i have to have fun",
"i have to be lied to I'll open a news paper.",
"i have to spend every night with him",
"i have to read it",
"i have to be invisible among dead leaves",
"i have to go to :(",
"i have to believe so that an angel passes",
"i have to come back.",
"i have to eat tho!",
"i have to shout “Kiss me now or lose me forever!",
"i have to reinstall the game again.",
"i have to understand this more.",
"i have to go on a disney trip soon...",
"i have to say thank you to the team over @HTMLCOIN who helped me this week, great platform and fantastic team.",
"i have to know is where Al got the AIDS from.",
"i have to gain more mutuals😊💗",
"i have to lose weight me: i want skinny legs me: i want a flat stomach me: i have to be thin me: *eats mcdonalds*",
"i have to hang out!!!?",
"i have to live my life.",
"i have to buy myself for Valentine’s Day this year!",
"i have to go on record as saying ""no surprise about trump not approving Dem memo/facts to be released on FBI/FISA topic.",
"i have to love you.",
"i have to go to France ",
"i have to order one",
"i have to be rich enough to smell a glass of wine before I drink it.",
"i have to be at that point in my life where my wife and I host our friends when they bring over dinner and we talk about dry, red wines",
"i have to purchase a hoodie my brother @formyblockchi",
"i have to protect you even in friendship.",
"i have to chat",
"i have to see confirmation that the change is permanent.",
"i have to thank you for being so special with me my life, two happy",
"i have to SING YOU A WONDERFULL SONG",
"i have to be a sappy asshole",
"i have to thank my feeding tube for saving my life and keeping me alive.",
"i have to thank you very much for the 700K, you guys are amazing and support us so much that I try to always bring the…",
"i have to watch all of them NBC!!!",
"i have to exchange EXO taiwan ticket.",
"i have to SINCERELY THANK YOU ALL FOR RETWEETING | LIKING THIS POST!",
"i have to go hiking",
"i have to apologize to our fans.",
"i have to say to someone but never get the courage to do so and it pisses me off bc if i could do it, it would make my life easier.",
"i have to leave Utah and never come back.",
"i have to be a singer not a programmer.",
"i have to hear from you.",
"i have to isolate myself, then I hate being in my own head s…",
"i have to be held.",
"i have to kms = i have to kim minseok",
"i have to watch some video on youtube..",
"i have to fly",
"i have to trust them but can't.",
"i have to like or rt it",
"i have to take this time to clown all the celebs i know who thought Trump would be positive for POC.",
"i have to see you but you're not mine",
"i have to know you more &gt;&gt;",
"i have to commission more Persona fan artists in the future.",
"i have to go on a hike",
"i have to kick his ass even though i feel the same about myself",
"i have to be what you are.",
"i have to do is step out and have a great time ✨",
"i have to go dancing💃🏽",
"i have to travel and see the world before I die #bucketlist",
"i have to graduate exactly in four years,, )",
"i have to confess my feelings to @ErikaSkenderas 😩😩😩",
"i have to deeply apologize to anyone, if you’ve experienced any hate due to your skin color, it’s disgusting and no one…",
"i have to go to europe but i spend my money as soon as i get it lovely",
"i have to be filled in both ends @timtales_com #bbbh #bareback #barebackfucker ",
"i have to just enjoy the art instead of hearing what you hoes gotta say",
"i have to",
"i have to believe this, but what if his investigation is not able to continue if the AG or Deputy restrict the scope of what he is allowed to pursue?",
"i have to convey it with my song""",
"i have to discuss wajib ada pen and my book.",
"i have to go to Disneyland :,(",
"i have to be an amazing writer.",
"i have to say, that I was wrong.",
"i have to be V and Jin",
"i have to play it usbdjs",
"i have to eat but im not hungry and too lazy to get off my bed",
"i have to do more with her character",
"i have to try this relationship thing again but i ain’t trying to take no L’s and be out here looking stupid.",
"i have to tell you how this thing works but im afraid if I do my enemies will catch on and things will change.",
"i have to be comfortable",
"i have to be @JoeyRyanOnline #GrabMyKawk",
"i have to see them again and again.",
"i have to enter lol",
"i have to see how my life is doing😂",
"i have to request @BTS_twt #MicDropRemix ",
"i have to know how the social worker affords such a nice apartment.",
"i have to accomplish, then resolve to pay the price to get it.",
"i have to scream was horrible before smartphones with maps I go to pick kids up from school cant even find their classes",
"i have to tweet like I'm famous but I have nothing to promote",
"i have to disappear.",
"i have to know is...",
"i have to see @RosannaPansino take home a #ShortyAward this year!",
"i have to come home to this",
"i have to cut my wrists.",
"i have to b inlove",
"i have to make you feel better and give you kisses”",
"i have to thank you for your support in these trying times.",
"i have to buy socks.",
"i have to so bad!",
"i have to be seem to read this book and enjoy this particular book.",
"i have to be around these days is my mama",
"i have to be taller.",
"i have to put my whole heart into replying and it’s hard for me to do that when i’m tired!!!",
"i have to give Buckeye Nation a ton of credit for the sell out.",
"i have to post things, however this internet won’t let me right now.",
"i have to reach 110lbs by April?",
"i have to party like, I’m so bored I’m gonna cry",
"i have to Speak To Your Manager, Newly Certified Yoga Instructor White Woman Realness.",
"i have to fly their",
"i have to love you always in all I do and say.",
"i have to rewatch it cause I forgot what happened!",
"i have to know which song, Bhaskar",
"i have to wake up to",
"i have to tell her, BUT luckily we have letters for that cause i could never say it in person",
"i have to #win Click Clack Lumberjack #game from @MaydayGames in @SahmReviews 2017 Mega #Giveaway.",
"i have to fight myself",
"i have to meet them so bad😭❤",
"i have to watch Black Panther because of the Afrofuturist aesthetics.",
"i have to learn Korean and Japanese 😭✌",
"i have to hug all the people who helped them see, *despite* terrible church teaching, that God wanted to help them, and use medicine to do it.",
"i have to go to church so bad",
"i have to prove him wrong.",
"i have to rinse a little piggyyy.",
"i have to meet Paco!!",
"i have to share ",
"i have to go to Jamaica someone come w/ me",
"i have to taste you but your lips are venomous poison...",
"i have to punch him!",
"i have to feel like I’m being cooked pls what’s all this warm nonsense",
"i have to curse him out so bad because I miss him😩 but that would be so childish of me😂",
"i have to wish goodmorning, goodafternoon, goodevening and goodnight!",
"i have to give you one of the simplest but…",
"i have to see how he reacts to being nicknamed ""Creepy Joe"" by President Trump..",
"i have to wake up to this valentines is my phone saying ",
"i have to wake up withyou every single day forever 💞👑👄💄🦋🦁🦁xxx",
"i have to be a skater with common sense and knowledge” #YuzuruHanyu, Kateigaho 2018.",
"i have to see someone Tebow across the ice.",
"i have to see what my friends are up not whole freaking world besides my friends are up to",
"i have to have a session, a makeout session..",
"i have to be a happier person",
"i have to become a lawyer there’s so much bullshit my race goes through in this fucked up country all I wanna do is put an end to it",
"i have to put my trust in everything my teammates and I have been work…",
"i have to win any ALTOS mummy bag from TETON Sports.",
"i have to live my life in such a way that when I get out of bed in the morning, the devil says, ""aw shit, he's up!",
"i have to swim, and maybe eat some lettuce.",
"i have to avoid any *Imperial Tango*.",
"i have to farm something...",
"i have to hold your hand, hold you in my arms and sing to you all night.",
"i have to share it but it didn't look good the past few times i rendered it",
"i have to be next to fuck this little twink",
"i have to hear micdrop…",
"i have to stream TALA by Maris more.",
"i have to say I love @StepUpSeries.",
"i have to do with you what spring does with the cherry trees.",
"i have to make about this but I'll do it in a separate tweet",
"i have to be your Knight 💖",
"i have to do something smh",
"i have to tell you one last time, how much you break me down and fix me a…",
"i have to now",
"i have to talk to you",
"i have to work with you",
"i have to blow my self up",
"i have to throat punch her because nothing should be more important that finding a place for your CHILD to live!!!!",
"i have to see all the pics of all the donuts even though i’ll be super envious lol.",
"i have to see them live",
"i have to know how Gemma and pasta boy have so much free time to shitpost.",
"i have to work with him in the studio.",
"i have to - Could It Be Different?",
"i have to see do more of ty it's an amazing pumpkin not going to lie",
"i have to be at the Alexander wang fashion show right now",
"i have to kill myself.",
"i have to wear a sweater and kakis while she's in a bikini",
"i have to see you on the finals okay!",
"i have to talk to my mutuals but im shy so nvm",
"i have to eat burger and fries or anything basta spicy 😬",
"i have to go out tonight, but my bed is calling me at the same time.",
"i have to make specific mention to Starlin Castro & JT Realmuto.",
"i have to feel u so deeply...",
"i have to read this.",
"i have to be in your deepest thoughts and your best orgasms.",
"i have to report an issue.",
"i have to see is if boy #1 is at the party with boy #2 but i caNT FIND THEIR STORIES",
"i have to SPEAK TO",
"i have to do that Tag!",
"i have to go to, she’ll buy extra tickets so I can bring “my friends” but little does she know, I only have 2 friends, and if they’re busy, I end up alone, feeling bad about myself, and w/ extra tickets 🙃",
"i have to be an Aggie so bad!!!",
"i have to represent me in parliament.",
"i have to spend my life with",
"i have to see what he’s having for dessert, I say yes and he takes a Live Photo of me 😂",
"i have to literally claw my fucking eyes out",
"i have to be a Bear 😂 I think I'm a little bit addicted to Snapchat...",
"i have to take a picture but I accidentally press the video button before.",
"i have to suck it so badly!",
"i have to turn it off 😒",
"i have to design for more brands",
"i have to help more...",
"i have to go back to sleep already :(",
"i have to maintain today.",
"i have to STEAL THAT DOG",
"i have to  be shown off like a fortnite win or it’s a no go",
"i have to cry all the time ☹️.",
"i have to say I love you【Dance with my secret】",
"i have to hug you right now",
"i have to live in whatever fantasy world Fox News and their viewers live in because apparently Hillary Clinton is President of…",
"i have to go to."
};

int x, min_x, max_x;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  
  display.setTextSize(TEXT_SIZE);
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  x = display.width();
  min_x = -6 * TEXT_SIZE * strlen(tweets[0]); // 12 = 6 pixels/character * text size 2
  max_x = min_x * -1;
  
  display.clearDisplay();
  delay(1);
}

bool scrolling_right = false;
bool scrolling_left = false;
int current_tweet = 0;

void loop() {
  int sensorValue = 201;
  //int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);

  if (!scrolling_right && sensorValue > 200) {
    x += 2;
    if (x > display.width()) { 
      x = min_x;
      current_tweet++;

      if (current_tweet >= NUM_TWEETS) {
        current_tweet = 0;
      }

      min_x = -6 * TEXT_SIZE * strlen(tweets[current_tweet]);
      max_x = min_x * -1;
    }
  }
  else if (!scrolling_left && sensorValue <= 50) {
    //if (--x < min_x) x = display.width();
    x -= 2;
    if (x < min_x) { 
      x = max_x;
      current_tweet--;

      if (current_tweet <= 0) {
        current_tweet = NUM_TWEETS - 1;
      }

      min_x = -6 * TEXT_SIZE * strlen(tweets[current_tweet]);
      max_x = min_x * -1;
    }
  }

  display.clearDisplay();
  display.setCursor(x, 0);
  display.print(tweets[current_tweet]);
  //display.setCursor(x, 20);
  //display.print(timestamps[current_tweet]);
  display.display();  
}
