#include "squib.h"

// Squib::Squib(uint8_t FIREHI, uint8_t FIRELO, uint8_t TESTHI, uint8_t TESTLO, uint8_t CONTHI, uint8_t CONTLO, uint8_t channelNumber){
//   PIN_FIREHI = FIREHI;
//   PIN_FIRELO = FIRELO;
//   PIN_TESTHI = TESTHI;
//   PIN_TESTLO = TESTLO;
//   PIN_CONTHI = CONTHI;
//   PIN_CONTLO = CONTLO;
//   channel = channelNumber;
// }

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

fireState Squib::getState(){
  return SQUIB_STATE;
}

double Squib::test(){
  digitalWrite(PIN_TESTHI, HIGH);
  digitalWrite(PIN_TESTLO, HIGH);

  unsigned int contHi = analogRead(PIN_CONTHI);
  unsigned int contLo = analogRead(PIN_CONTLO);

  delay(50);

  digitalWrite(PIN_TESTHI, LOW);
  digitalWrite(PIN_TESTLO, LOW);

  // Rlower = 800 + Rsquib
  // VsquibHi = Vcc * ((Rlower || 4k)/(1k + (Rlower || 4k)))
  // contHi = VsquibHi * 0.25 * 1024/3.3     // ADC units
  // VsquibLo = VsquibHi * 800/Rlower
  // contLo = VsquibLo * 0.25 * 1024/3.3     // ADC units

  // VsquibHi - VsquibLo = VsquibHi*(1 - (800/Rlower))
  // (VsquibLo/VsquibHi) = (800/RLower) = 800/(800 - Rsquib)
  // 800 * VsquibHi / VsquibLo = 800 - Rsquib
  // Rsquib = 800 * ((VsquibHi / VsquibLo) - 1) = 800 * (contHi - contLo)/contLo

  //SerialUSB.println(contLo);
  //SerialUSB.println(contHi);

  //if(contLo < LO_SHORT_THRESHOLD) return LOW_SIDE_FAULT;
  //if(contHi > HI_SHORT_THRESHOLD) return HIGH_SIDE_FAULT;

  double res = (800.0 * (contHi - contLo)) / contLo;

  return (double) contLo;
}

void Squib::arm(){
  SQUIB_STATE = ARMED;
}

void Squib::disarm(){
  SQUIB_STATE = DISARMED;
  setLow();
}

bool Squib::fire(unsigned long countdown, uint16_t fireTime) { // MILLISECONDS!!!
  
  if(SQUIB_STATE == ARMED){
    this->fireTime = fireTime;
    fireStartTime = millis();
    ignite();
    return true;
  } else {
    return false;
  }
  
  /*if(countdown < 10000){ // ignore firing with countdowns of less than ten seconds, to give some recovery time for safety
    SQUIB_STATE = FIRE_ABORT;
    return;
  }

  if(SQUIB_STATE == ARMED){
    SQUIB_STATE = FIRE_COUNTDOWN;
    COUNTDOWN = countdown;
    COUNTDOWN_START = millis();
    this->fireTime = fireTime;
    }*/
}

void Squib::update() {
  if (SQUIB_STATE == FIRING && fireStartTime + fireTime < millis()) {
    disarm();
  }
}

unsigned long Squib::updateCountdown(){
  if (SQUIB_STATE != FIRE_COUNTDOWN) return -1;

  if(millis() < COUNTDOWN_START){ // if there's been a rollover, or other error
    SQUIB_STATE = FIRE_ABORT;
    return -1;
  }

  long countdown_remaining = COUNTDOWN - (millis() - COUNTDOWN_START); // remaining time, in milliseconds
  if(countdown_remaining <= 0){
    SQUIB_STATE = FIRING;
    ignite();
  }

  return countdown_remaining;
}

void Squib::setHigh() {
  digitalWrite(PIN_FIREHI, HIGH);
  digitalWrite(PIN_FIRELO, HIGH);
}

void Squib::setLow() {
  digitalWrite(PIN_FIREHI, LOW);
  digitalWrite(PIN_FIRELO, LOW);
}

void Squib::ignite() {
  //sayPrayer();
  digitalWrite(PIN_FIREHI, HIGH);
  digitalWrite(PIN_FIRELO, HIGH);

  //delay(fireTime);

  //digitalWrite(PIN_FIREHI, LOW);
  //digitalWrite(PIN_FIRELO, LOW);

  SQUIB_STATE = FIRING;
}

void Squib::sayPrayer(){
  SerialUSB.println("1 Corinthians 3:13");
  SerialUSB.println("their work will be shown for what it is, because the Day will bring it to light. It will be revealed with fire, and the fire will test the quality of each person’s work.");
}
