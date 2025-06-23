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
    String msg = Serial1.readStringUntil('\n');
    msg.trim();
    Serial.println(msg);
    //check if its servo message
    if(msg.equals(targetMsg)){
      for(int pos = 0; pos<=180;pos++){
        Serial.println("Front" + String(pos)); //debugging
        servo.write(pos);
        delay(15);
      }

      for(int pos = 180; pos>=0;pos--){
        Serial.println("Back" + String(pos)); //debugging
        servo.write(pos);
        delay(15);
      }
      delay(15);
    }
  }else{
    Serial.println("Unknown message");
  }
}

