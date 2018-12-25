#include <Arduino.h>
#include "MC33797.h"
#include <SPI.h>

const int slaveSelectPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode (slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH);
  SPI.begin();
}

void loop(){
  delay(1000);
  Squib_Init();
}

extern "C" {
  void debug(const char * data){
    Serial.println(data);
  }

  void debug_hex(uint8_t data){
    Serial.println(data,HEX);
  }

  uint8_t send(uint8_t data){
    debug("sending!");
    digitalWrite(slaveSelectPin, LOW);
    uint8_t val = SPI.transfer(data);
    digitalWrite(slaveSelectPin, HIGH);
    return val;
  }
}