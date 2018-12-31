#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) cmd_force_event_t {
  unsigned event : 4;
} cmd_force_event_t;

class CMD_FORCE_EVENT : public Packet{
protected:
const size_t length = sizeof(cmd_force_event_t);
const uint8_t id = 0x6;

uint4.0_t event;

public:
uint4.0_t get_event() { return event; }
void set_event(uint4.0_t new_val) { event = new_val; }


void read(char* buf, size_t len){
  cmd_force_event_t encoded;
  memcpy(&encoded,buf,len);
  //convert event
}


void write(Writeable& dest){
  cmd_force_event_t encoded;
  //convert event
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static CMD_FORCE_EVENT g_CMD_FORCE_EVENT;
