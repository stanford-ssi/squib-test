#include "squib.h"

Squib::Squib(uint8_t FIREHI, uint8_t FIRELO, uint8_t TESTHI, uint8_t TESTLO, uint8_t CONTHI, uint8_t CONTLO){
  PIN_FIREHI = FIREHI;
  PIN_FIRELO = FIRELO;
  PIN_TESTHI = TESTHI;
  PIN_TESTLO = TESTLO;
  PIN_CONTHI = CONTHI;
  PIN_CONTLO = CONTLO;
}
