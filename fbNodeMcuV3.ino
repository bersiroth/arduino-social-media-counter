#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
//Include the SSL client
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>
#include "Variables.h"
#include "Matrice.h"
#include "Utils.h"
//#include "IRremote.h"

WiFiClientSecure client;

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
  String headers = "";
  String body = "";
  bool finishedHeaders = false;
  bool currentLineIsBlank = true;
  bool gotResponse = false;
  long now;
  char host[] = "graph.facebook.com";

  if (client.connect(host, 443)) {
    debug("Client connected");

    String URL = "/v2.12/" + FBpageId + "?fields=fan_count&access_token=" + FBaccessToken;

    debug("Facebook API uri : " + URL);

    client.println("GET " + URL + " HTTP/1.1");
    client.print("Host: "); client.println(host);
    client.println("User-Agent: arduino/1.0");
    client.println("");

    now = millis();
    // checking the timeout
    while (millis() - now < 1500) {
      while (client.available()) {
        char c = client.read();

        if (finishedHeaders) {
          body = body + c;
        } else {
          if (currentLineIsBlank && c == '\n') {
            finishedHeaders = true;
          }
          else {
            headers = headers + c;
          }
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }

        //marking we got a response
        gotResponse = true;

      }

      if (gotResponse) {
        DynamicJsonBuffer jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(body);
        if (root.success()) {
          fan = root["fan_count"].as<String>();
        } else {
          Serial.println("failed to parse JSON");
        }

        break;
      }
    }
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
