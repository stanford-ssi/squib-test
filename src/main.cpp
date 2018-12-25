#include <Arduino.h>
#include "MC33797.h"

void setup() {
  Serial.begin(9600);
}

void loop(){
  delay(1000);
  Squib_Init();
}

extern "C" {
  void debug(const char * data){
    Serial.println(data);
  }
}