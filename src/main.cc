#include <Arduino.h>
#include <wiring_private.h>
#include "SSIradio.h"
#include "squib.h"

void displayState(Squib& sq);
void writeLEDs(uint8_t bitmask, uint8_t state);
void contTest(Squib sq);

// LED pin definitions - numbered left to right, with text upright
#define LED1  5 // PA15
#define LED2  2 // PA14
#define LED3 38 // PA13
#define LED4 22 // PA12
#define LED5 24 // PB11
#define LED6 23 // PB10

#define SRAD_TX 35
#define SRAD_RX 36

const uint8_t NUM_LEDS = 6;
const uint8_t LEDS[] = {LED1, LED2, LED3, LED4, LED5, LED6};
const uint8_t LED_CHANNEL_GROUPS[] = {0b000111, 0b111000};
#define BLINK_INTERVAL 100 // milliseconds
unsigned long blinkPeriods = 0;
unsigned long lastBlink = 0;
unsigned long msg_interval = 3000;

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

Uart SerialS6C(&sercom1, SRAD_RX, SRAD_TX, SERCOM_RX_PAD_2, UART_TX_PAD_0);

void SERCOM1_Handler()
{
  SerialS6C.IrqHandler();
}

SSIradio S6C;

//const char *ack_message = "RECEIVED";

unsigned long last_report = 0;

Squib SQUIB_A = Squib(SQUIB_A_FIREHI, SQUIB_A_FIRELO, SQUIB_A_TESTHI, SQUIB_A_TESTLO, SQUIB_A_CONTHI, SQUIB_A_CONTLO, 0);
Squib SQUIB_B = Squib(SQUIB_B_FIREHI, SQUIB_B_FIRELO, SQUIB_B_TESTHI, SQUIB_B_TESTLO, SQUIB_B_CONTHI, SQUIB_B_CONTLO, 1);

void flourishLEDs(){
  for (uint8_t i = 0; i < 6; i++) {
    digitalWrite(LEDS[i], HIGH);
    delay(50);
    digitalWrite(LEDS[i], LOW);
    delay(50);
  }
}

void barLEDs(int num){
  for (uint8_t i = 0; i < 6; i++) {
    if(i >= 6-num){
      digitalWrite(LEDS[i], HIGH);
    }else{
      digitalWrite(LEDS[i], LOW);
    }
  }
}

void receiveMsg(char* msg) {
  SerialUSB.println(msg);
  if (msg[1] == 'a') {
    SQUIB_A.arm();

  } else if (msg[1] == 'f') {
    SQUIB_A.fire();
    S6C.tx("Commanded fire");

  } else if (msg[1] == 'd') {
    SQUIB_A.disarm();
    S6C.tx("DISARMED");
    barLEDs(0);

  } else if (msg[1] == 't') {
    contTest(SQUIB_A);
  }
}

void setup()
{
  SQUIB_A.init();
  SQUIB_B.init();

  for (uint8_t i = 0; i < 6; i++) {
    pinMode(LEDS[i], OUTPUT);
  }

  flourishLEDs();
  //SQUIB_A.arm();
  //SQUIB_A.fire();

  SerialUSB.begin(115200);
  //while (!SerialUSB);

  S6C.set_callback(receiveMsg);
  S6C.begin(9600, &SerialS6C);
  while (!S6C);

  //delay(5000);
}

void loop()
{

  if(SerialUSB.available()){
    digitalWrite(LED1, HIGH);
    char buf[64];
    SerialUSB.readBytes(buf, 64);
    receiveMsg(buf);
    delay(100);
    digitalWrite(LED1, LOW);
  }

  static bool led_state = false;

  if(millis() - lastBlink > BLINK_INTERVAL){
    lastBlink = millis();
    blinkPeriods++;
    //writeLEDs(0b1, led_state);
    led_state = !led_state;
  }

  S6C.rx();
  displayState(SQUIB_A);
  //displayState(SQUIB_B);

  if (millis() - last_report > msg_interval) {
    contTest(SQUIB_A);
    //SerialUSB.println("potato");
    // Update report time
    last_report = millis();
  }

  delay(10);
}

void displayState(Squib& sq){

  long cnt = sq.updateCountdown();

  // this logic doesn't work if using both squib channels but we're not so /shrug
  if(cnt > 5000 && cnt < 20000){
    msg_interval = 2000;
  }else if(cnt > 0){
    msg_interval = 1000;
  }else{
    msg_interval = 3000;
  }

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
      if(cnt > 15000) barLEDs(4);
      else if(cnt > 10000) barLEDs(3);
      else if(cnt > 5000) barLEDs(2);
      else barLEDs(1);

      break;
    case POST_FIRE:
      barLEDs(0);

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

void contTest(Squib sq){
  float res = sq.test();
  char out[16];
  snprintf(out, 16, "%f %d", res, sq.getState());
  S6C.tx(out);
  SerialUSB.println(out);
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
