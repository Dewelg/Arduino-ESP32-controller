#include <Arduino.h>
#include <WiFi.h>

//declarations
const char* id = "";
const char* password = "";
const char* host = "";
const int port = 5000;

WiFiClient client;


void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  delay(10);

  WiFi.begin(id, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.print("Wifi Connected");


}

void loop() {
  if(!client.connected()){
    if(client.connect(host, port)){
      //Connect to sever and send confirmation message
      Serial.println("Connected to sever");
      client.println("Hello from ESP32");

      //Recieve sever message and print message
      String response = client.readStringUntil('\n');
      client.flush();
      Serial.println("Response from sever: " + response);

      //Send string to mega
      Serial2.write(response.c_str());

      client.stop();
    } else {
      Serial.println("Connection Failed");
      delay(5000);
    }
  }
}

