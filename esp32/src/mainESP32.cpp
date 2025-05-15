#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>

//declarations
const char* id = "";
const char* password = "";
const char* host = "";
const int port = 5000;

WiFiClient client;


void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(id, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.print("Wifi Connected");
}

void loop() {
  if(client.connect(host, port)){
    Serial.println("Connected to sever");
    client.print("Hello from ESP32");
    String response = client.readStringUntil('\n');
    Serial.println("Response from sever: " + response);
    client.stop();
  } else{
    Serial.println("Connection Failed");
    delay(5000);
  }
}

