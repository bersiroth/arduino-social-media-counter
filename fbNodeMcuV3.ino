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

HttpClient http;

long checkDueTime;
int checkDelay = 3000;

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
  String host = "graph.facebook.com";
  String URL = "/v2.12/" + FBpageId + "?fields=fan_count&access_token=" + FBaccessToken;
  String body = http.get("graph.facebook.com", "/v2.12/" + FBpageId + "?fields=fan_count&access_token=" + FBaccessToken);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(body);
  if (root.success()) {
    fan = root["fan_count"].as<String>();
  } else {
    Serial.println("failed to parse JSON");
  }
  
  return fan;
}

void facebookScreen()
{
    // String facebookFan = getFacebookFan();
    String facebookFan = "14";
    int fbLength = static_cast<int>(facebookFan.length());

    if (facebookFan != "") {
      debug("Nb facebook fan : " + facebookFan);
      debug("First integer : " + facebookFan[0] - '0');

      size_t number_of_zero = 4 - fbLength;

      for (int i = 0; i < number_of_zero; i++) {
        facebookFan = "0" + facebookFan;
      }

      debug("String convert for display : " + facebookFan);

      for (int i = 0; i < 4; i++) {
        matrice.displayNumber(matrice.allNumbers[facebookFan[i] - '0'], i+1);
      }

      matrice.displayLogo(matrice.FbLogo, matrice.FbLogoColors);
      matrix.show();
    } else {
      debug("Error facebook fan.");
    }
}

void loop() {
  long now = millis();
  if (now >= checkDueTime) {
    debug("---------");
    facebookScreen();
    debug("---------");
    checkDueTime = now + checkDelay;
  }
}
