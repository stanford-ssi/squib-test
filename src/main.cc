#include <Arduino.h>
#include "SSIradio.h"

SSIradio S6C;

const char *ack_message = "RECEIVED";

unsigned long last_report = 0;

void setup()
{

  for (size_t i = 0; i < 5; i++) {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }

  Serial.begin(9600);
  //while (!Serial);
  S6C.begin(9600, &Serial1);
  //while (!S6C);

  delay(5000);
}

void loop()
{
  //S6C.rx();

  if (millis() - last_report > 5000) {

  //S6C.tx();

    // Update report time
    last_report = millis();
  }

  delay(10);
}

// extern "C"
// {
//   void debug(const char *data)
//   {
//     Serial.println(data);
//   }
//
//   void debug_hex(uint8_t data)
//   {
//     Serial.println(data, HEX);
//   }
//
//   void debug_bin(uint8_t data)
//   {
//     Serial.println(data, BIN);
//   }
//
//   uint8_t send(uint8_t data)
//   {
//     digitalWrite(slaveSelectPin, LOW);
//     uint8_t val = SPI.transfer(data);
//     digitalWrite(slaveSelectPin, HIGH);
//     return val;
//   }
// }
