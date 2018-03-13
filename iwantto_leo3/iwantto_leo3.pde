import processing.serial.*;

import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.MessageFormat;
import processing.sound.SoundFile;

static final String TTS_SERVICE_URL = "http://localhost:8080/get-speech?tweet_id={0}";
static final String TWEET_SERVICE_URL = "http://localhost:8080/get-tweet?find={0}&replace={1}";

static final String TWEET_FIND = "I want to";
static final String TWEET_REPLACE = "I have to";
//static final int TWEET_INTERVAL_MILLIS = 15000; // This should match the Docker Server's Interval

String tweetUrl;
String speechFile;


//int interval_tweet = 350;
//int interval_voice = 320;

boolean twitter_flag = false;
boolean button = false;

SoundFile speech;
SoundFile ding;
Serial myPort;                      

PFont font;
PFont font2;

int arduinoInput =0;
int inByte;
boolean firstContact = false;

/*
Get Tweet and Speech from Docker Container. The tweet will be either:
 1. The latest tweet within the last interval window (online)
 2. A random tweet from the local database of collected tweets (online or offline)
 */

void setup() {
  
  println(Serial.list());
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  
  
  try {
    String tweetFind = URLEncoder.encode(TWEET_FIND, "UTF-8");
    String tweetReplace = URLEncoder.encode(TWEET_REPLACE, "UTF-8");
    tweetUrl = MessageFormat.format(TWEET_SERVICE_URL, tweetFind, tweetReplace);
    speechFile = File.createTempFile("tweet", ".mp3").getAbsolutePath();
  } 
  catch (UnsupportedEncodingException e) {
  }
  catch (IOException e) {
  }

  //size(720, 480);
  fullScreen();

  ding = new SoundFile(this, "ding.mp3");
  font = loadFont("HelveticaNeue-Bold-48.vlw");
  font2 = loadFont("HelveticaNeue-48.vlw");

  textFont(font);
  textAlign(CENTER, CENTER);
  textSize(20);
  background(100);
  frameRate(30);
  drawTweet();
}

void draw() {  
  
  if (twitter_flag) {
      drawTweet();
  }
  
  println(inByte);
  
  
}


void drawTweet() {
  String tweetJson = String.join("\n", loadStrings(tweetUrl));
  JSONObject tweet = parseJSONObject(tweetJson);

  if (tweet.isNull("Error")) {
    String tweetText = tweet.getString("TweetText").toUpperCase();
    String tweetTime = tweet.getString("TweetTimestamp");
    String ttsUrl = MessageFormat.format(TTS_SERVICE_URL, tweet.getString("TweetId"));
    saveBytes(speechFile, loadBytes(ttsUrl));
    background(random(255),random(255),random(255));
    textFont(font, 60);
    rectMode(CENTER);
    fill(random(255),random(255),random(255));
    text(tweetText, width/2, height/2-10, width-60, height-10);
    
    textFont(font2, 20);
    fill(random(255),random(255),random(255));
    text(tweetTime, width/2, height-40, width-60, height-10);
    
   

    speech = new SoundFile(this, speechFile);
    speech.rate(0.5);
    speech.play();
    //delay(10000);
    
  } else if (tweet.getString("Error").equals("NOT_FOUND")) {
    String msg = MessageFormat.format("No Matching Tweets in tweets.db for {0}:{1}. You must set the server to accumulate these Tweets First", TWEET_FIND, TWEET_REPLACE);
    System.err.println(msg);
  }
}

void serialEvent(Serial myPort) {
  inByte = myPort.read();

  if (firstContact == false) {
    if (inByte == 'A') {
      myPort.clear();          // clear the serial port buffer
      firstContact = true;     // you've had first contact from the microcontroller
      myPort.write('A');       // ask for more
    }
  } else {
    // Add the latest byte from the serial port to array:
    arduinoInput = inByte;

   // println(arduinoInput);
    // Send a capital A to request new sensor readings:
    myPort.write('A');
    // Reset serialCount:
  }
  
  if (inByte == 9) {
    twitter_flag = true;
    println("hello");
  } else {
    twitter_flag = false;
  }
  
}
  