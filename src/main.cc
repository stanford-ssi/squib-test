#include <Arduino.h>
#include "SSIradio.h"

//#define S6C Serial1

SSIradio S6C;

const char *ack_message = "RECEIVED";

unsigned long last_report = 0;

// void min_tx_start(uint8_t port) {}
// void min_tx_finished(uint8_t port) {}
// uint16_t min_tx_space(uint8_t port)
// {
//   return S6C.availableForWrite();
// }

void setup()
{
  //stat = new Squib_StatusType();

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
  S6C.rx();

  if (millis() - last_report > 5000) {

  S6C.tx();

    /*
    // Send squib resistances on port 1
    snprintf(buf + header_size, buf_size, "R1A: %d/R1B: %d", stat->Squib_Stat1AResistance,
            stat->Squib_Stat1BResistance);
    buf_len = strlen(buf + header_size) + 1;
    buf[0] = 0;
    buf[1] = buf_len + header_size;
    min_send_frame(&min_ctx, cur_min_id++, (uint8_t *)buf, (uint8_t)buf_len + header_size);

    // Send squib resistances on port 2
    snprintf(buf + header_size, buf_size, "R2A: %d/R2B: %d", stat->Squib_Stat2AResistance,
            stat->Squib_Stat2BResistance);
    buf_len = strlen(buf + header_size) + 1;
    buf[0] = 0;
    buf[1] = buf_len + header_size;
    min_send_frame(&min_ctx, cur_min_id++, (uint8_t *)buf, (uint8_t)buf_len + header_size);
    */

    // Update report time
    last_report = millis();
  }

  delay(10);

  /*
  if (millis() % 1000 > 500 && millis() % 1000 < 550) {
    digitalWrite(13, LOW);
  }
  */

/*
  Squib_StatusType *s = new Squib_StatusType();
  while (true)
  {
    int ret;
    ret = Squib_GetStatus(s);
    Serial.print("Status: ");
    Serial.println(ret);
    Serial.print("1A Resistance: ");
    Serial.println(stat->Squib_Stat1AResistance, BIN);
    Serial.print("1B Resistance: ");
    Serial.println(stat->Squib_Stat1BResistance, BIN);
    Serial.print("2A Resistance: ");
    Serial.println(stat->Squib_Stat2AResistance, BIN);
    Serial.print("2B Resistance: ");
    Serial.println(stat->Squib_Stat2BResistance, BIN);

    Serial.print("Enable 1: ");
    Serial.println(stat->Squib_StatFen1);
    Serial.print("Enable 2: ");
    Serial.println(stat->Squib_StatFen2);

    if (Serial.available())
    {
      int code = Serial.parseInt();
      if (code == 1)
        ret = Squib_Fire(CMD_FIRE_1A);
      if (code == 2)
        ret = Squib_Fire(CMD_FIRE_1B);
      if (code == 3)
        ret = Squib_Fire(CMD_FIRE_2A);
      if (code == 4)
        ret = Squib_Fire(CMD_FIRE_2B);
      Serial.print("Fire: ");
      Serial.println(ret);
    }
  }
*/
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
