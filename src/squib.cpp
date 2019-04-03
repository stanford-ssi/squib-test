#include "squib.h"

Squib::Squib(uint8_t FIREHI, uint8_t FIRELO, uint8_t TESTHI, uint8_t TESTLO, uint8_t CONTHI, uint8_t CONTLO){
  PIN_FIREHI = FIREHI;
  PIN_FIRELO = FIRELO;
  PIN_TESTHI = TESTHI;
  PIN_TESTLO = TESTLO;
  PIN_CONTHI = CONTHI;
  PIN_CONTLO = CONTLO;
}

// safely initialize squib

void Squib::init(){
  pinMode(PIN_FIREHI, OUTPUT);
  digitalWrite(PIN_FIREHI, LOW);
  pinMode(PIN_FIRELO, OUTPUT);
  digitalWrite(PIN_FIRELO, LOW);

  pinMode(PIN_TESTHI, OUTPUT);
  digitalWrite(PIN_TESTHI, LOW);
  pinMode(PIN_TESTLO, OUTPUT);
  digitalWrite(PIN_TESTLO, LOW);

  pinMode(PIN_CONTHI, INPUT);
  pinMode(PIN_CONTLO, INPUT);
}

int Squib::test(){
  return 0;
}

void Squib::arm(){

}

void Squib::disarm(){

}

void Squib::fire(){

}
