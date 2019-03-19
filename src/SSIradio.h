#ifndef SSI_RADIO
#define SSI_RADIO

#include <Arduino.h>
#include "min.h"

#ifndef NUM_RADIOS
#define NUM_RADIOS 1
#endif

uint8_t num_radios_initialized = 0;
SSIradio &radios[NUM_RADIOS];

class SSIradio
{
public:
  uint8_t swID;
  uint16_t hwID = -1;

  SSIradio(Stream &serial);
  void set_min_id(uint8_t new_min_id);
  // void configureRF();
  // void encode_and_transmit(void *msg_data, uint8_t msg_size);
  // uint8_t tryToRX(void *msg_data, uint8_t msg_size);
  // uint8_t getRSSI();
  // String getSyndrome();
  // RH_RF24 *rf24;    //the RadioHead Driver Object
  // void configureLED();
  // void LEDOn(bool = false);
  // void LEDOff(bool = false);
  // void blinkStatus(int blinks);

private:
  struct min_context min_ctx;
  uint8_t cur_min_id;
  Stream &serial_port;

  // void RadioOff();
  // void RadioOn();
  // void configurePins();
  // uint8_t lastRssi; //RSSI of last reception
  // String errorSyndrome;
};

#endif
