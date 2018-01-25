import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.MessageFormat;
import processing.sound.SoundFile;

final String TTS_SERVICE_URL = "http://twitter.martysullivan.com/text-to-speech?text={0}";
final String TWEET_SERVICE_URL = "http://twitter.martysullivan.com/tweet-replace?find={0}&replace={1}";
final String TWEET_FIND = "I want to";
final String TWEET_REPLACE = "I have to";

int animationStart = -1;
String tweetUrl;
SoundFile mp3;

String tweetText = "";
File mp3File;

void setup() {
  size(800, 800);
  textAlign(CENTER, CENTER);
  textSize(20);
  background(0);
  
  try {    
    String tweetFind = URLEncoder.encode(TWEET_FIND, "UTF-8");
    String tweetReplace = URLEncoder.encode(TWEET_REPLACE, "UTF-8");
    tweetUrl = MessageFormat.format(TWEET_SERVICE_URL, tweetFind, tweetReplace);
    mp3File = File.createTempFile("tweet", ".mp3");
  } 
  catch (UnsupportedEncodingException e) { }
  catch (IOException e) { }
}

void draw() {
  if (!tweetText.equals("")) {
    text(tweetText, 10, 10, 780, 780);
    mp3 = new SoundFile(this, mp3File.getAbsolutePath());
    mp3.rate(0.5);
    mp3.play();
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
    
    saveBytes(mp3File.getAbsolutePath(), loadBytes(ttsUrl));
  } 
  catch (UnsupportedEncodingException e) { }
}