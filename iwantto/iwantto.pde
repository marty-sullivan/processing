import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.MessageFormat;
import processing.sound.SoundFile;

static final String TTS_SERVICE_URL = "http://twitter.martysullivan.com/text-to-speech?text={0}";
static final String TWEET_SERVICE_URL = "http://twitter.martysullivan.com/tweet-replace?find={0}&replace={1}";
static final String TWEET_FIND = "I want to";
static final String TWEET_REPLACE = "I have to";

String tweetText;
String tweetUrl;
File speechFile;
SoundFile speech;

void setup() {
  size(800, 800);
  textAlign(CENTER, CENTER);
  textSize(20);
  background(0);
  
  try {    
    String tweetFind = URLEncoder.encode(TWEET_FIND, "UTF-8");
    String tweetReplace = URLEncoder.encode(TWEET_REPLACE, "UTF-8");
    tweetText = "";
    tweetUrl = MessageFormat.format(TWEET_SERVICE_URL, tweetFind, tweetReplace);
    speechFile = File.createTempFile("tweet", ".mp3");
  } 
  catch (UnsupportedEncodingException e) { }
  catch (IOException e) { }
}

void draw() {
  if (!tweetText.equals("")) {
    text(tweetText, 10, 10, 780, 780);
    speech = new SoundFile(this, speechFile.getAbsolutePath());
    speech.rate(0.5);
    speech.play();
    tweetText = "";
  }
  else {
    background(0);
    delay(10000);
    getTweet();
  }
}

void getTweet() {
  try {
    String tweetJson = String.join("\n", loadStrings(tweetUrl));
    JSONObject tweet = parseJSONObject(tweetJson);
    tweetText = tweet.getString("replaced") + System.getProperty("line.separator") + System.getProperty("line.separator") + tweet.getString("timestamp");   
    String encodedTweet = URLEncoder.encode(tweet.getString("replaced"), "UTF-8");
    String ttsUrl = MessageFormat.format(TTS_SERVICE_URL, encodedTweet);
    
    saveBytes(speechFile.getAbsolutePath(), loadBytes(ttsUrl));
  } 
  catch (UnsupportedEncodingException e) { }
}