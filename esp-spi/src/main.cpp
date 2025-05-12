#include <Arduino.h>
#include <SPI.h>

// put function declarations here:
int myFunction(int, int);

SPIClass SPI2(VSPI);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);

  SPI2.begin(18,23,19,5);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}