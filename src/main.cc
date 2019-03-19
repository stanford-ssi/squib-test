#include <Arduino.h>
//#include "MC33797.h"
#include <SPI.h>
#include "min.h"

#define S6C Serial1

const size_t header_size = 2;
const size_t buf_size = 64;
const char *ack_message = "RECEIVED";

char buf[buf_size];
size_t buf_len;

struct min_context min_ctx;
uint8_t cur_min_id;
unsigned long last_report = 0;

uint32_t min_time_ms(void)
{
  return millis();
}

void min_application_handler(uint8_t min_id, uint8_t *min_payload,
    uint8_t len_payload, uint8_t port)
{
  // increment min_id to be sequential
  cur_min_id = min_id + 1;

  // send acknowledgement message
  /*
  size_t ack_size = strlen(ack_message);
  char ack_buf[ack_size + 2];
  ack_buf[0] = 0;
  ack_buf[1] = strlen(ack_message);
  strncpy(ack_buf + 2, ack_message, ack_size);
  min_send_frame(&min_ctx, cur_min_id++, (uint8_t *)ack_buf, (uint8_t)ack_size + 2);
  */

  // Serial.println("Aw hell yeah");
  Serial.write((char *) min_payload, len_payload);
  Serial.println(*min_payload);
  if (((char *)min_payload)[1] == 'X') {
    Serial.println("BOOM BOOM ACKA-LACKA BOOM BOOM");
  }
  if (((char *)min_payload)[1] == 'Z') {
    Serial.println("NO BOOM NO BOOM");
  } }

void min_tx_start(uint8_t port) {}
void min_tx_finished(uint8_t port) {}
uint16_t min_tx_space(uint8_t port)
{
  return S6C.availableForWrite();
}

void min_tx_byte(uint8_t port, uint8_t byte)
{
  // TODO fixme
  S6C.write(&byte, 1U);
  Serial.write(&byte, 1U);
}

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
  S6C.begin(9600);
  while (!S6C);

  delay(5000);

  min_init_context(&min_ctx, 0);
}

void loop()
{
  if (S6C.available() > 0) {
    buf_len = S6C.readBytes(buf, buf_size);
  } else {
    buf_len = 0;
  }
  min_poll(&min_ctx, (uint8_t *)buf, (uint8_t)buf_len);

  if (millis() - last_report > 5000) {

    buf[0] = 0;
    buf[1] = 5;
    buf[2] = 'H';
    buf[3] = 'E';
    buf[4] = 'L';
    buf[5] = 'L';
    buf[6] = '\0';

    Serial.println("hello");
    min_send_frame(&min_ctx, cur_min_id++, (uint8_t *)buf, 7);


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
