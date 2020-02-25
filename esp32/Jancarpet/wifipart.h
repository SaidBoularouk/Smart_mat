#include <WiFi.h>

const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPassword";

bool connectToNetwork() {
  bool isconnected = false;
  if (ssid != "" && password != "") {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Establishing connection to WiFi..");
      isconnected = false;
    }
    Serial.println("Connected to network");
    isconnected = true;
  } else {
    isconnected = false;
  }
  return isconnected;
}

//void setup() {
//
//  Serial.begin(115200);
//
//  scanNetworks();
//  connectToNetwork();
//
//  Serial.println(WiFi.macAddress());
//  Serial.println(WiFi.localIP());
//
//  WiFi.disconnect(true);
//  Serial.println(WiFi.localIP());
//
//}
//
//void loop() {}
