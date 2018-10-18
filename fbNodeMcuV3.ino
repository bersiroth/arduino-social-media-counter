#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
//Include the SSL client
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>
#include "Variables.h"
#include "Matrice.h"
#include "Utils.h"
#include "HttpClient.h"
//#include "IRremote.h"

unsigned long now = 0;
unsigned long previous_millis = 0;
int interval = 10000;
int state = 0;

HttpClient http;

/*long checkDueTime;*/
/*int checkDelay = 30000;*/

//const int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

const int brocheLEDs = 3;
const int luminosite = 10;

const int pannelHeight = 8;
const int pannelWidth = 32;
const int nombreLEDs = pannelHeight * pannelWidth;
Adafruit_NeoPixel matrix = Adafruit_NeoPixel(nombreLEDs, brocheLEDs);
Matrice matrice = Matrice(&matrix);

//IRrecv irrecv(receiver);     // create instance of 'irrecv'
//decode_results results;      // create instance of 'decode_results'

void setup()
{
  Serial.begin(115200);

  matrix.begin();
  matrix.setBrightness(luminosite);
  //Serial.println("IR Receiver Button Decode");
  //irrecv.enableIRIn(); // Start the receiver

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  debug("Connecting Wifi: ");
  debug(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    debug(".", false);
    delay(500);
  }
  debug("");
  debug("WiFi connected");
  debug("IP address: ");
  IPAddress ip = WiFi.localIP();
  // debug(ip);

}

String getFacebookFan()
{
  String fan = "";
  char* host = "graph.facebook.com";
  String URL = "/v2.12/" + FBpageId + "?fields=fan_count&access_token=" + FBaccessToken;
  String body = http.get(host, URL);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(body);
  if (root.success()) {
    fan = root["fan_count"].as<String>();
  } else {
    Serial.println("failed to parse JSON Facebook");
  }
  
  return fan;
}


String getYoutubeSub()
{
  String subs = "";
  char* host = "www.googleapis.com";
  String URL = "/youtube/v3/channels?id=" + YTpageId + "&part=statistics&key=" + YtaccessToken;
  String body = http.get(host, URL);

  DynamicJsonBuffer jsonBuffer;
  debug(body);
  JsonObject& root = jsonBuffer.parseObject(body);
  if (root.success()) {
    subs = root["items"][0]["statistics"]["subscriberCount"].as<String>();
  } else {
    Serial.println("failed to parse JSON youtube");
  }
  
  return subs;
}

String getTwitterFollower()
{
  String follower = "";
  char* host = "cdn.syndication.twimg.com";
  String URL = "/widgets/followbutton/info.json?screen_names=linkvalue";
  String body = http.get(host, URL);

  DynamicJsonBuffer jsonBuffer;
  JsonArray& root = jsonBuffer.parseArray(body);
  if (root.success()) {
    follower = root[0]["followers_count"].as<String>();
  } else {
    Serial.println("failed to parse JSON Twitter");
  }
  
  return follower;
}

void display(String follower, Logo logo)
{
  int followerLength = static_cast<int>(follower.length());

  if (follower != "") {
    debug("Nb follower : " + follower);
    debug("First integer : " + follower[0] - '0');

    size_t number_of_zero = 4 - followerLength;

    for (int i = 0; i < number_of_zero; i++) {
      follower = "0" + follower;
    }

    debug("String convert for display : " + follower);

    for (int i = 0; i < 4; i++) {
      matrice.displayNumber(matrice.allNumbers[follower[i] - '0'], i+1);
    }

    matrice.displayLogo(logo);
    matrix.show();
  } else {
    debug("Error display");
  }
}

void loop() {
  /*long now = millis();*/
  now = millis();
  /*if (now >= checkDueTime) {*/
    /*debug("---------");*/
    /*display(getFacebookFan(), Logo::facebook);*/
    /*delay(2000);*/
    /*debug("---------");*/
    /*display(getTwitterFollower(), Logo::twitter);*/
    /*debug("---------");*/
    /*checkDueTime = now + checkDelay;*/
  /*}*/
  if(now - previous_millis >= interval) {
    previous_millis = now;
    switch (state) {
      case 0: state++;
              display(getFacebookFan(), Logo::facebook);
              break;
      case 1: state++;
              display(getTwitterFollower(), Logo::twitter);
              break;
      case 2: state = 0;
              display(getYoutubeSub(), Logo::youtube);
              break;
    }
  }
}
