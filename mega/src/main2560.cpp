#include <Arduino.h>
#include <SPI.h>
#include <Servo.h>

//declarations
Servo servo;

const char targetMsg[] = "Servo on";

void setup() {
  Serial.begin(115200);

  servo.attach(3);
  
  pinMode(53, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(53) == LOW){
    char recivedData = SPI.transfer(0);
    Serial.println(recivedData);
  }
}

