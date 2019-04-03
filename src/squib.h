#ifndef SQUIB
#define SQUIB

#include <Arduino.h>

class Squib
{
public:
  Squib(uint8_t FIREHI, uint8_t FIRELO, uint8_t TESTHI, uint8_t TESTLO, uint8_t CONTHI, uint8_t CONTLO);
  void init();
  int test();
  void disarm();
  void arm();
  void fire();
private:

  uint8_t PIN_FIREHI;
  uint8_t PIN_FIRELO;
  uint8_t PIN_TESTHI;
  uint8_t PIN_TESTLO;
  uint8_t PIN_CONTHI;
  uint8_t PIN_CONTLO;

};

#endif
