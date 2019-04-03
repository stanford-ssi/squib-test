#include <Arduino.h>
//#include "SSIradio.h"
#include "squib.h"

void displayState(Squib& sq);
void writeLEDs(uint8_t bitmask, uint8_t state);

// LED pin definitions - numbered left to right, with text upright
#define LED1  5 // PA15
#define LED2  2 // PA14
#define LED3 38 // PA13
#define LED4 22 // PA12
#define LED5 24 // PB11
#define LED6 23 // PB10

const uint8_t NUM_LEDS = 6;
const uint8_t LEDS[] = {LED1, LED2, LED3, LED4, LED5, LED6};
const uint8_t LED_CHANNEL_GROUPS[] = {0b111000, 0b000111};
#define BLINK_INTERVAL 100 // milliseconds
unsigned long blinkPeriods = 0;
unsigned long lastBlink = 0;

// Squib firing pin definitions
#define SQUIB_A_TESTLO  4 // PA08
#define SQUIB_A_CONTLO A3 // PA04
#define SQUIB_A_TESTHI  3 // PA09
#define SQUIB_A_CONTHI A4 // PA05
#define SQUIB_A_FIREHI  0 // PA11
#define SQUIB_A_FIRELO  1 // PA10

#define SQUIB_B_TESTLO A0 // PA02
#define SQUIB_B_CONTLO A1 // PB08
#define SQUIB_B_TESTHI 25 // PA03
#define SQUIB_B_CONTHI A2 // PB09
#define SQUIB_B_FIREHI  9 // PA07
#define SQUIB_B_FIRELO  8 // PA06

//SSIradio S6C;

const char *ack_message = "RECEIVED";

unsigned long last_report = 0;

Squib SQUIB_A = Squib(SQUIB_A_FIREHI, SQUIB_A_FIRELO, SQUIB_A_TESTHI, SQUIB_A_TESTLO, SQUIB_A_CONTHI, SQUIB_A_CONTLO, 0);
Squib SQUIB_B = Squib(SQUIB_B_FIREHI, SQUIB_B_FIRELO, SQUIB_B_TESTHI, SQUIB_B_TESTLO, SQUIB_B_CONTHI, SQUIB_B_CONTLO, 1);

void setup()
{
  SQUIB_A.init();
  SQUIB_B.init();

  for (uint8_t i = 0; i < 6; i++) {
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], HIGH);
    delay(50);
    digitalWrite(LEDS[i], LOW);
    delay(50);
  }

  SerialUSB.begin(9600);
  //while (!Serial);
  //S6C.begin(9600, &Serial1);
  //while (!S6C);

  delay(5000);
}

void loop()
{
  if(millis() - lastBlink > BLINK_INTERVAL){
    lastBlink = millis();
    blinkPeriods++;
  }

  displayState(SQUIB_A);
  displayState(SQUIB_B);
  //S6C.rx();

  if (millis() - last_report > 5000) {

  //S6C.tx("potato");

    // Update report time
    last_report = millis();
  }

  delay(10);
}

void displayState(Squib& sq){

  sq.updateCountdown();

  switch(sq.getState()){
    case DISARMED:
      writeLEDs(LED_CHANNEL_GROUPS[sq.channel], LOW);
      break;
    case ARMED:
      if(blinkPeriods & 0b10){
        writeLEDs(LED_CHANNEL_GROUPS[sq.channel], HIGH);
      }else{
        writeLEDs(LED_CHANNEL_GROUPS[sq.channel], LOW);
      }
      break;
    case FIRE_COUNTDOWN:
      if(blinkPeriods & 0b1){ // blink faster
        writeLEDs(LED_CHANNEL_GROUPS[sq.channel], HIGH);
      }else{
        writeLEDs(LED_CHANNEL_GROUPS[sq.channel], LOW);
      }
      break;
    default:
      break;
  }
}

void writeLEDs(uint8_t bitmask, uint8_t state){
  uint8_t bitmarker = 0b000001;
  for(size_t i = 0; i < NUM_LEDS; i++){
    if(bitmarker & bitmask) digitalWrite(LEDS[i], state);
    bitmarker = bitmarker << 1;
  }
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
