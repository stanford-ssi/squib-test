#include <Arduino.h>
//#include "SSIradio.h"
#include "squib.h"

// LED pin definitions - numbered left to right, with text upright
#define LED1  5 // PA15
#define LED2  2 // PA14
#define LED3 38 // PA13
#define LED4 22 // PA12
#define LED5 24 // PB11
#define LED6 23 // PB10

const uint8_t LEDS[] = {LED1, LED2, LED3, LED4, LED5, LED6};

// Squib firing definitions
#define SQUIB_A_TESTLO  2 // PA08
#define SQUIB_A_CONTLO A3 // PA04
#define SQUIB_A_TESTHI  3 // PA09
#define SQUIB_A_CONTHI A4 // PA05
#define SQUIB_A_FIREHI  0 // PA11
#define SQUIB_A_FIRELO  1 // PA10

#define SQUIB_B_TESTLO A0 // PA02
#define SQUIB_B_CONTLO A1 // PB08
#define SQUIB_B_TESTHI 15 // PA03
#define SQUIB_B_CONTHI A2 // PB09
#define SQUIB_B_FIREHI  9 // PA07
#define SQUIB_B_FIRELO  8 // PA06

//SSIradio S6C;

const char *ack_message = "RECEIVED";

unsigned long last_report = 0;

void setup()
{
  for (uint8_t i = 0; i < 6; i++) {
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], HIGH);
    delay(100);
    digitalWrite(LEDS[i], LOW);
    delay(100);
  }

  //Serial.begin(9600);
  //while (!Serial);
  //S6C.begin(9600, &Serial1);
  //while (!S6C);

  delay(5000);
}

void loop()
{
  //S6C.rx();

  if (millis() - last_report > 5000) {

  //S6C.tx("potato");

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
