#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) cmd_force_state_t {
  unsigned state : 4;
} cmd_force_state_t;
static_assert(sizeof(cmd_force_state_t) == 1, "cmd_force_state_t: unexpected packed length");

class CMD_FORCE_STATE : public Packet{
protected:
const size_t length = sizeof(cmd_force_state_t);
const uint8_t id = 0x5;

uint8_t state;

public:
uint8_t get_state() { return state; }
void set_state(uint8_t new_val) { state = new_val; }


void read(char* buf, size_t len){
  cmd_force_state_t encoded;
  memcpy(&encoded,buf,len);
  //convert state
}


void write(Writeable& dest){
  cmd_force_state_t encoded;
  //convert state
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static CMD_FORCE_STATE g_CMD_FORCE_STATE;
