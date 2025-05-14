#include <Arduino.h>
#include <SPI.h>

//declarations
SPIClass SPI2(VSPI);

void setup() {
  Serial.begin(115200);

  //enable spi and config pins
  SPI2.begin(18, 19, 23, 5);
  pinMode(5, OUTPUT);
}

void loop() {
  
}

