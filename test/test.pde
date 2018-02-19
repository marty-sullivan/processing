PFont font;
PFont font2;

String tweetText = "I HAVE TO TEXT YOU, MISS YOU, HUG YOU, LAUGH WITH YOU, JOKE WITH YOU, HOLD YOU, KISS YOU, CHILL WITH YOU, AND LOVE YOU";
String tweetTime = "STOCKHOLEM, 07:30PM, 02/14/2018";

void setup() {
  //size(720, 480);
  fullScreen();

  font = loadFont("HelveticaNeue-Bold-48.vlw");
  font2 = loadFont("HelveticaNeue-48.vlw");

  textFont(font);
  textAlign(CENTER, CENTER);
}

void draw() {
  background(random(255), random(255), random(255));

  textFont(font, 25);
  rectMode(CENTER);
  fill(random(255), random(255), random(255));
  text(tweetText, width/2, height/2-10, width-60, height-10);

  textFont(font2, 14);
  fill(random(255), random(255), random(255));
  text(tweetTime, width/2, height-40, width-60, height-10);

  delay(5000);
}