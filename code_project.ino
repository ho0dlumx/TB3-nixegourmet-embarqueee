#include <WiFi.h>
#include <HTTPClient.h>
#define LED 26

const char* ssid = "Wi-Fi Maison des Élèves"; //Wifi network name
const char* password = "w1f1delaME139"; //Wifi network password

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  pinMode(LED, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    digitalWrite(LED,LOW);
  }
  Serial.println("Connected to WiFi");
  digitalWrite(LED,HIGH);
  delay(2000);
  digitalWrite(LED,LOW);
  
}

void loop() {
  if (Serial.available() > 0) {
    String barcode = Serial.readStringUntil('\n'); //barcode entry with scan
    if (barcode.length() > 0) {
      HTTPClient http;
      //String url = "http://localhost:8000/integration/"+barcode+".html";
      //String url = "http://IP:8000/integration/"+barcode+".html";
      String url = "http://linkedin." + barcode; //test to see if code works
      http.begin(url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.println("Page opened: " + url);
        digitalWrite(LED,HIGH); #visual test
      } else {
        Serial.println("Error opening page");
      }
      http.end();
    }
  }
}
