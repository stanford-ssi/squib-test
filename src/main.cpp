#include <Arduino.h>
#include "MC33797.h"
#include <SPI.h>

const int slaveSelectPin = 10;
const int enablePin = 9;

void setup() {
  Serial.begin(9600);
  pinMode (slaveSelectPin, OUTPUT);
  pinMode (enablePin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH);
  digitalWrite(enablePin, HIGH);
  SPI.begin();
}

void loop(){
  delay(1000);
  uint8_t ret = Squib_Init();
  Serial.print("Init: ");
  Serial.println(ret);
  delay(1000);
  ret = Squib_Fire(CMD_FIRE_1A);
  Serial.print("Fire: ");
  Serial.println(ret);
  delay(1000);
  ret = Squib_Fire(CMD_FIRE_NO_SQUIBS);
  Serial.print("Fire: ");
  Serial.println(ret);
}

extern "C" {
  void debug(const char * data){
    Serial.println(data);
  }

  void debug_hex(uint8_t data){
    Serial.println(data,HEX);
  }

  void debug_bin(uint8_t data){
    Serial.println(data,BIN);
  }

  uint8_t send(uint8_t data){
    digitalWrite(slaveSelectPin, LOW);
    uint8_t val = SPI.transfer(data);
    digitalWrite(slaveSelectPin, HIGH);
    return val;
  }
}