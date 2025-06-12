#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
// #include <WiFiManager.h>

//declarations
const char* id = "";
const char* password = "";
const char* host = "";
const int port = 5000;

WiFiClient client;
SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(id, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.print("Wifi Connected");

  SPI.begin();
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
}

void loop() {
  if(!client.connected()){
    if(client.connect(host, port)){
      Serial.println("Connected to sever");
      client.println("Hello from ESP32");
      String response = client.readStringUntil('\n');
      client.flush();
      Serial.println("Response from sever: " + response);
      delay(100);
      client.stop();

      int length = response.length() + 1;
      char* message = new char[length];
      strcpy(message, response.c_str());

      digitalWrite(5, LOW);
      SPI.beginTransaction(spiSettings);

      for(int i = 0; i<length;i++){
        SPI.transfer(message[i]);
      }
      
      SPI.endTransaction();
      digitalWrite(5, HIGH);

      delete[] message;

      delay(1000);
    } else {
      Serial.println("Connection Failed");
      delay(5000);
    }
  }
}

