#include "SSIradio.h"

uint8_t num_radios_initialized = 0;
SSIradio* radios[NUM_RADIOS];

//SSIradio:
//Constructs a new S6C/radio object
SSIradio::SSIradio(){}

//begin
//actually initializes a new radio on the specified serial port with the specified baud rate
void SSIradio::begin(uint16_t baud, HardwareSerial *serial){
  serial_port = serial;
  serial_port->begin(baud);

  swID = num_radios_initialized; // assign radio software ID in order it was initialized
  radios[swID] = this; // load reference to this radio into radios array
  num_radios_initialized++;
  min_init_context(&min_ctx, swID); // use swID as min port number

  //TODO get hardware ID from radio
}

//set_min_id
//sets message id in min
void SSIradio::set_min_id(uint8_t new_min_id){
  cur_min_id = new_min_id;
}

//rx
//
uint8_t SSIradio::rx(){

  if (serial_port->available() > 0) {
    buf_len = serial_port->readBytes(buf, buf_size);
  } else {
    buf_len = 0;
  }
  min_poll(&min_ctx, (uint8_t *)buf, (uint8_t)buf_len);

  return buf_len;
}

void SSIradio::tx(){

      buf[0] = 0;
      buf[1] = 5;
      buf[2] = 'H';
      buf[3] = 'E';
      buf[4] = 'L';
      buf[5] = 'L';
      buf[6] = '\0';

      min_send_frame(&min_ctx, cur_min_id++, (uint8_t *)buf, 7);
}

// legitimate min functions

void min_application_handler(uint8_t min_id, uint8_t *min_payload,
    uint8_t len_payload, uint8_t port)
{
  // increment min_id to be sequential
  radios[port]->set_min_id(min_id + 1);

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

  // Serial.write((char *) min_payload, len_payload);
  // Serial.println(*min_payload);
  // if (((char *)min_payload)[1] == 'X') {
  //   Serial.println("BOOM BOOM ACKA-LACKA BOOM BOOM");
  // }
  // if (((char *)min_payload)[1] == 'Z') {
  //   Serial.println("NO BOOM NO BOOM");
  // }
}

void min_tx_byte(uint8_t port, uint8_t byte)
{
  // // TODO fixme
  // S6C.write(&byte, 1U);
  // Serial.write(&byte, 1U);

  radios[port]->serial_port->write(&byte, 1U); // sends outgoing byte to radio
}

uint16_t min_tx_space(uint8_t port)
{
  return radios[port]->serial_port->availableForWrite();
}

// placeholder min functions

void min_tx_start(uint8_t port) {}

void min_tx_finished(uint8_t port) {}

uint32_t min_time_ms(void)
{
  return millis();
}
