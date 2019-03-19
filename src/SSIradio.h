#ifndef NUM_RADIOS
#define NUM_RADIOS 1
#endif

#ifndef SSI_RADIO
#define SSI_RADIO

#include <Arduino.h>
#include "min.h"

const size_t header_size = 2;
const size_t buf_size = 64;

class SSIradio
{
public:
  uint8_t swID;
  uint16_t hwID = -1;
  HardwareSerial* serial_port;

  SSIradio();
  void begin(uint16_t baud, HardwareSerial *serial);
  void set_min_id(uint8_t new_min_id);
  uint8_t rx();
  void tx();

private:
  struct min_context min_ctx;
  uint8_t cur_min_id;

  char buf[buf_size];
  size_t buf_len;
};

#endif
