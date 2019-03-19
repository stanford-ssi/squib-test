#include "SSIradio.h"

//SSIradio:
//Constructs a new S6C object
SSIradio::SSIradio(Stream &serial)
{
  serial_port = serial;
  min_init_context(&min_ctx, 0);
  swID = num_radios_initialized; // assign radio software ID in order it was initialized
  radios[swID] = &this; // load reference to this radio into radios array
  num_radios_initialized++;

  //TODO get hardware ID from radio
}

void set_min_id(uint8_t new_min_id){
  min_id = new_min_id;
}

void min_application_handler(uint8_t min_id, uint8_t *min_payload,
    uint8_t len_payload, uint8_t port)
{
  // increment min_id to be sequential
  cur_min_id = min_id + 1;

  // send acknowledgement message
  /*
  size_t ack_size = strlen(ack_message);
  char ack_buf[ack_size + 2];
  ack_buf[0] = 0;
  ack_buf[1] = strlen(ack_message);
  strncpy(ack_buf + 2, ack_message, ack_size);
  min_send_frame(&min_ctx, cur_min_id++, (uint8_t *)ack_buf, (uint8_t)ack_size + 2);
  */

  // Serial.println("Aw hell yeah");
  Serial.write((char *) min_payload, len_payload);
  Serial.println(*min_payload);
  if (((char *)min_payload)[1] == 'X') {
    Serial.println("BOOM BOOM ACKA-LACKA BOOM BOOM");
  }
  if (((char *)min_payload)[1] == 'Z') {
    Serial.println("NO BOOM NO BOOM");
  }
}

// placeholder min functions

void min_tx_start(uint8_t port) {}

void min_tx_finished(uint8_t port) {}

uint32_t min_time_ms(void)
{
  return millis();
}
