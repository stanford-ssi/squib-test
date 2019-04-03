#ifndef SQUIB
#define SQUIB

#include <Arduino.h>

typedef enum {
DISARMED,
ARMED,
FIRE_COUNTDOWN,
FIRING,
POST_FIRE,
CONT_FAIL
} fireState;

class Squib
{
public:
  uint8_t channel;

  Squib(uint8_t FIREHI, uint8_t FIRELO, uint8_t TESTHI, uint8_t TESTLO, uint8_t CONTHI, uint8_t CONTLO, uint8_t channelNumber);
  void init();
  int test();
  void disarm();
  void arm();
  void fire();
  fireState getState();
private:

  uint8_t PIN_FIREHI;
  uint8_t PIN_FIRELO;
  uint8_t PIN_TESTHI;
  uint8_t PIN_TESTLO;
  uint8_t PIN_CONTHI;
  uint8_t PIN_CONTLO;

  fireState SQUIB_STATE = DISARMED;

};

#endif
