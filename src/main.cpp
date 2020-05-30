#include <Arduino.h>

#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

#include "secrets.h"
#include "calibration.h"

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY; 
char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password

int fromLow = LUFTWERT;
int fromHigh = WASSERWERT;


WiFiClient  client;

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D5, OUTPUT);

  digitalWrite(D0, HIGH);
  digitalWrite(D5, LOW);

  Serial.begin(9600);
  delay(100);

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  int valueA0 = analogRead(A0);
  ThingSpeak.setField(1, valueA0);
  valueA0 = map(valueA0, fromLow, fromHigh, 0, 100);
  ThingSpeak.setField(2, valueA0);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(20000);
}