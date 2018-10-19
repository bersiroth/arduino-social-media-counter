#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
//Include the SSL client
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>
#include <neotimer.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "Variables.h"
#include "Matrice.h"
#include "Utils.h"
#include "HttpClient.h"

int state = 0;
const int interval = 10000;
const int receiver = 14; // Signal Pin of IR receiver to Arduino Digital Pin 11
const int brocheLEDs = 3;
const int luminosite = 10;

const int pannelHeight = 8;
const int pannelWidth = 32;
const int nombreLEDs = pannelHeight * pannelWidth;

String facebookFan;
String twitterFollower;
String youtubeSub;

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(nombreLEDs, brocheLEDs);
Matrice matrice = Matrice(&matrix);
HttpClient http;
Neotimer timer = Neotimer(interval);
Neotimer fetchingDataTimer = Neotimer(600000);
IRrecv irrecv(receiver);
decode_results results;

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
  facebookFan = fan;

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
  youtubeSub = subs;

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
  twitterFollower = follower;

  return follower;
}

void fetchData()
{
  debug("Fetching Facebook fans");
  getFacebookFan();
  debug("Fetching Twitter followers");
  getTwitterFollower();
  debug("Fetching YouTube subscribers");
  getYoutubeSub();
}

void setup()
{
  Serial.begin(115200);

  matrix.begin();
  matrix.setBrightness(luminosite);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver

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
  debug(ip);

  fetchData();
}

void display(String follower, Logo logo)
{
  int followerLength = static_cast<int>(follower.length());

  if (follower != "") {
    matrice.displayLogo(logo);

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

    matrix.show();
  } else {
    debug("Error display");
  }
}

void screen() {
  switch (state) {
    case 0: state++;
            display(facebookFan, Logo::facebook);
            break;
    case 1: state++;
            display(twitterFollower, Logo::twitter);
            break;
    case 2: state = 0;
            display(youtubeSub, Logo::youtube);
            break;
  }
}

void ir_controller() {
  serialPrintUint64(results.value, HEX);
  switch (results.value) {
    case 0xFFC23D: timer.repeatReset();
                   state =  state != 2 ? state + 1 : 0;
                   break;
    case 0xFF22DD: timer.repeatReset();
                   state =  state != 0 ? state - 1 : 2;
                   break;
  }

  screen();
  irrecv.resume();
}

void loop() {
  if (fetchingDataTimer.repeat()) {
    fetchData();
  }

  if (timer.repeat()) {
    screen();
  }

  if (irrecv.decode(&results)){
    ir_controller();
  }
}
