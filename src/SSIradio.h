#ifndef NUM_RADIOS
#define NUM_RADIOS 1
#endif

#ifndef SSI_RADIO
#define SSI_RADIO

#include <Arduino.h>
#include "min.h"
#include "RadioInterface.h"

const size_t header_size = 2;
const size_t buf_size = 64;
const size_t MAX_PAYLOAD_SIZE = buf_size - 3;

class SSIradio
{
  typedef void (*CallbackType) (char*);
public:
  uint8_t swID;
  uint16_t hwID = -1;
  HardwareSerial* serial_port;
  uint8_t msg_count = 0;
  CallbackType callback = NULL;
  char buf[buf_size];
  size_t buf_len;

  SSIradio();
  void begin(unsigned long baud, HardwareSerial *serial);
  void set_min_id(uint8_t new_min_id);
  uint8_t rx();
  void tx(const char* buffer_in);
  void tx(const char* buffer_in, size_t length);
  void tx(char msgtype, const char* buffer_in, size_t length);
  void set_callback(CallbackType callback_fn);

  operator bool() const;

private:
  struct min_context min_ctx;
  uint8_t cur_min_id;
};

#endif
