#ifndef SQUIB
#define SQUIB

#include <Arduino.h>

#define HI_SHORT_THRESHOLD 900
#define LO_SHORT_THRESHOLD 100

#define HIGH_SIDE_FAULT -1000
#define LOW_SIDE_FAULT -2000

typedef enum {
DISARMED,
ARMED,
FIRE_COUNTDOWN,
FIRING,
POST_FIRE,
FIRE_ABORT
} fireState;

class Squib
{
public:
  uint8_t channel;

  Squib(uint8_t FIREHI, uint8_t FIRELO, uint8_t TESTHI, uint8_t TESTLO, uint8_t CONTHI, uint8_t CONTLO, uint8_t channelNumber):
    channel(channelNumber),
    PIN_FIREHI(FIREHI),
    PIN_FIRELO(FIRELO),
    PIN_TESTHI(TESTHI),
    PIN_TESTLO(TESTLO),
    PIN_CONTHI(CONTHI),
    PIN_CONTLO(CONTLO){};
  void init();
  double test();
  void disarm();
  void arm();
  void fire(unsigned long countdown = 10000, uint16_t fireTime = 1000); // milliseconds!!!
  unsigned long updateCountdown();
  fireState getState();


private:

  void ignite();
  void sayPrayer();

  uint8_t PIN_FIREHI;
  uint8_t PIN_FIRELO;
  uint8_t PIN_TESTHI;
  uint8_t PIN_TESTLO;
  uint8_t PIN_CONTHI;
  uint8_t PIN_CONTLO;

  fireState SQUIB_STATE = DISARMED;
  unsigned long COUNTDOWN;
  unsigned long COUNTDOWN_START;
  uint16_t fireTime = 1000; // milliseconds!!!

};


#endif
