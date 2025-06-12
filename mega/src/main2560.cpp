#include <Arduino.h>
#include <SPI.h>
#include <Servo.h>

//declarations



void setup() {
  Serial.begin(115200);

  SPI.begin();
  pinMode(53, OUTPUT);
}

void loop() {
  if(digitalRead(53) == LOW){
    char recivedData = SPI.transfer(0);
    Serial.println(recivedData);
  }
}

