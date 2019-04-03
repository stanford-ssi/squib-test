#ifndef SQUIB
#define SQUIB

#include <Arduino.h>

class Squib
{
public:
  Squib();
private:

  uint8_t FIREHI;
  uint8_t FIRELO;
  uint8_t TESTHI;
  uint8_t TESTLO;
  uint8_t CONTHI;
  uint8_t CONTLO;

};

#endif
