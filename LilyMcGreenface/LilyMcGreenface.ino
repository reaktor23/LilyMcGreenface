/*
   Lily McGreenface

   Open source plant watering and monitoring via MQTT.

   Lily is Controlled by a WeMos D1 mini.

   Hardware & Connections:

      Capacitive soil moisture sensor v1.2
        - Connected to ADC pin A0

      Water Pump
        - Connected to 5v by a 2N7000 MOSFET
        - Gate is connected to digital pin D4

   Lily will send soil moisture level periodically to mqtt_humi_topic
   Lily will pump water for n seconds, defined by the messages that arrive to mqtt_water_topic


   This is a Reaktor23 Hackerspace project.
   More information on our website:
   www.reaktor23.org

*/



#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const String clientId = "LilyMcGreenface001";
const int pub_interval = 300;                     // send Sensor data every 5 minutes

// WiFi Credentials
const char* ssid = "........";
const char* password = "........";

// MQTT Settings
const char* mqtt_server = "broker.mqtt-dashboard.com";
const int   mqtt_port = 1883;
const char* mqtt_status_topic = "statusTopic";    // status information will get published to this topic.
const char* mqtt_humi_topic = "outTopic";         // soil humidity will get published to this topic.
const char* mqtt_water_topic = "inTopic";         // pump will be activated for n seconds, defined in messages that arrive in this topic.


WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish(mqtt_status_topic, "connected.");
      client.subscribe(mqtt_water_topic);
    } else {
      Serial.println("Failed connection to server. Try again in 3 seconds...");
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  for (int i = 1; i <= pub_interval; i++) {
    delay(1000);
  }

  client.publish(mqtt_status_topic, analogRead(A0));

}
