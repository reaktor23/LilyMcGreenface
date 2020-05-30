#include <Arduino.h>

#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>

 unsigned long myChannelNumber = SECRET_CH_ID;
 const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
 char ssid[] = SECRET_SSID;   // your network SSID (name)
 char pass[] = SECRET_PASS;   // your network password

WiFiClient  client;

void setup() {
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

  // Measure Analog Input (A0)
  int valueA0 = analogRead(A0);
  //int valueA0 = analogRead(A0);

  // Write value to Field 1 of a ThingSpeak Channel
  int httpCode = ThingSpeak.writeField(myChannelNumber, 1, valueA0, myWriteAPIKey);

  if (httpCode == 200) {
    Serial.println("Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  }

  // Wait 20 seconds to update the channel again
  delay(20000);
}