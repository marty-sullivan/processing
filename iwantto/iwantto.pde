import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.MessageFormat;
import processing.sound.SoundFile;

static final String TTS_SERVICE_URL = "http://localhost:8080/get-speech?tweet_id={0}";
static final String TWEET_SERVICE_URL = "http://localhost:8080/get-tweet?find={0}&replace={1}";

static final String TWEET_FIND = "I want to";
static final String TWEET_REPLACE = "I have to";
static final int TWEET_INTERVAL_MILLIS = 15000; // This should match the Docker Server's Interval

String tweetUrl;
String speechFile;
SoundFile speech;

/*
Get Tweet and Speech from Docker Container. The tweet will be either:
  1. The latest tweet within the last interval window (online)
  2. A random tweet from the local database of collected tweets (online or offline)
*/
void drawTweet() {  
  String tweetJson = String.join("\n", loadStrings(tweetUrl));
  JSONObject tweet = parseJSONObject(tweetJson);
  String tweetText = tweet.getString("TweetText").toUpperCase() + System.getProperty("line.separator") + System.getProperty("line.separator") + tweet.getString("TweetTimestamp");
  String ttsUrl = MessageFormat.format(TTS_SERVICE_URL, tweet.getString("TweetId"));
  saveBytes(speechFile, loadBytes(ttsUrl));

  background(0);
  text(tweetText, 10, 10, 780, 780);
  speech = new SoundFile(this, speechFile);
  speech.rate(0.5);
  speech.play();
}

void setup() {
  try {
    String tweetFind = URLEncoder.encode(TWEET_FIND, "UTF-8");
    String tweetReplace = URLEncoder.encode(TWEET_REPLACE, "UTF-8");
    tweetUrl = MessageFormat.format(TWEET_SERVICE_URL, tweetFind, tweetReplace);
    speechFile = File.createTempFile("tweet", ".mp3").getAbsolutePath();
  } 
  catch (UnsupportedEncodingException e) { }
  catch (IOException e) { }

  size(800, 800);
  //PFont font = createFont("AppleColorEmoji", 18);
  //textFont(font);
  textAlign(CENTER, CENTER);
  textSize(20);
  background(0);
  drawTweet();
}

void draw() {  
  delay(TWEET_INTERVAL_MILLIS);
  drawTweet();
}

