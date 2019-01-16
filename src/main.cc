#include <Arduino.h>
#include "MC33797.h"
#include <SPI.h>
#include "min.h"

#define S6C Serial1

struct min_context min_ctx;
uint8_t cur_min_id; 

uint32_t min_time_ms(void)
{
  return millis();
}

void min_application_handler(uint8_t min_id, uint8_t *min_payload,
    uint8_t len_payload, uint8_t port)
{
  if (*min_payload == 0x51) {
    Squib_Fire(CMD_FIRE_1A);
  }
  cur_min_id = min_id + 1;
}

const int slaveSelectPin = 10;
const int enablePin = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(slaveSelectPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH);
  digitalWrite(enablePin, HIGH);
  SPI.begin();

  delay(1000);
  uint8_t ret = Squib_Init();
  Serial.print("Init: ");
  Serial.println(ret);

  min_init_context(&min_ctx, 0);
}

void loop()
{
  char buf[32];
  size_t buf_len;
  if (S6C.available() > 0) buf_len = S6C.readBytes(buf, 32);
  else buf_len = 0;
  min_poll(&min_ctx, (uint8_t *)buf, (uint8_t)buf_len);

/*
  while (true)
  {
    Squib_StatusType *s = new Squib_StatusType();
    ret = Squib_GetStatus(s);
    Serial.print("Status: ");
    Serial.println(ret);
    Serial.print("1A Resistance: ");
    Serial.println(s->Squib_Stat1AResistance, BIN);
    Serial.print("1B Resistance: ");
    Serial.println(s->Squib_Stat1BResistance, BIN);
    Serial.print("2A Resistance: ");
    Serial.println(s->Squib_Stat2AResistance, BIN);
    Serial.print("2B Resistance: ");
    Serial.println(s->Squib_Stat2BResistance, BIN);

    Serial.print("Enable 1: ");
    Serial.println(s->Squib_StatFen1);
    Serial.print("Enable 2: ");
    Serial.println(s->Squib_StatFen2);

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

extern "C"
{
  void debug(const char *data)
  {
    Serial.println(data);
  }

  void debug_hex(uint8_t data)
  {
    Serial.println(data, HEX);
  }

  void debug_bin(uint8_t data)
  {
    Serial.println(data, BIN);
  }

  uint8_t send(uint8_t data)
  {
    digitalWrite(slaveSelectPin, LOW);
    uint8_t val = SPI.transfer(data);
    digitalWrite(slaveSelectPin, HIGH);
    return val;
  }
}
