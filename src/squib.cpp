#include "squib.h"

Squib::Squib(uint8_t FIREHI, uint8_t FIRELO, uint8_t TESTHI, uint8_t TESTLO, uint8_t CONTHI, uint8_t CONTLO, uint8_t channelNumber){
  PIN_FIREHI = FIREHI;
  PIN_FIRELO = FIRELO;
  PIN_TESTHI = TESTHI;
  PIN_TESTLO = TESTLO;
  PIN_CONTHI = CONTHI;
  PIN_CONTLO = CONTLO;
  channel = channelNumber;
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

fireState Squib::getState(){
  return SQUIB_STATE;
}

int Squib::test(){
  digitalWrite(PIN_TESTHI, HIGH);
  digitalWrite(PIN_TESTLO, HIGH);

  uint16_t contHi = analogRead(PIN_CONTHI);
  uint16_t contLo = analogRead(PIN_CONTLO);

  digitalWrite(PIN_TESTHI, LOW);
  digitalWrite(PIN_TESTLO, LOW);

  return contHi - contLo;
}

void Squib::arm(){
  SQUIB_STATE = ARMED;
}

void Squib::disarm(){
  SQUIB_STATE = DISARMED;
}

void Squib::fire(unsigned long countdown = 10000){ // MILLISECONDS!!! (defaults to 10000)

  if(countdown >= 10000){ // ignore firing with countdowns of less than ten seconds, to give some recovery time for safety
    if(SQUIB_STATE == ARMED){
      SQUIB_STATE = FIRE_COUNTDOWN;
      COUNTDOWN = countdown;
      COUNTDOWN_START = millis();
    }
  }
}

unsigned long Squib::updateCountdown(){
  if(millis() < COUNTDOWN_START){ // if there's been a rollover, or other error
    SQUIB_STATE = FIRE_ABORT;
    return -1;
  }

  long countdown_remaining = COUNTDOWN - (millis() - COUNTDOWN_START); // remaining time, in milliseconds
  if(countdown_remaining < 0){
    SQUIB_STATE = FIRING;
    ignite();
  }

  return countdown_remaining;
}

void Squib::ignite(){
  sayPrayer();
  digitalWrite(PIN_FIREHI, HIGH);
  digitalWrite(PIN_FIRELO, HIGH);

  delay(fireTime);

  digitalWrite(PIN_FIREHI, LOW);
  digitalWrite(PIN_FIRELO, LOW);

  SQUIB_STATE = POST_FIRE;
}

void sayPrayer(){
  SerialUSB.println("1 Corinthians 3:13");
  SerialUSB.println("their work will be shown for what it is, because the Day will bring it to light. It will be revealed with fire, and the fire will test the quality of each person’s work.");
}
