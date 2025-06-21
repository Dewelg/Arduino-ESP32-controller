#include <Arduino.h>
#include <Servo.h>

Servo servo;
const char targetMsg[] = "Servo on";

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  servo.attach(3);
}

void loop() {
  if(Serial1.available()){
    //check if its servo message
    String msg = Serial1.readStringUntil('\n');
    msg.trim();
    Serial.println("From ESP32: " + msg);
    if(msg.equals(targetMsg)){
      for(int pos = 0; pos<=180;pos++){
        servo.write(pos);
        delay(1000);
      }

      for(int pos = 180; pos>=0;pos--){
        servo.write(pos);
        delay(1000);
      }
    }
  }else{
    Serial.println("Unknown message");
  }
}

