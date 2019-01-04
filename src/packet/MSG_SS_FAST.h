#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) msg_ss_fast_t {
  unsigned state : 4;
  unsigned time : 28;
} msg_ss_fast_t;
static_assert(sizeof(msg_ss_fast_t) == 4, "msg_ss_fast_t: unexpected packed length");

class MSG_SS_FAST : public Packet{
protected:
const size_t length = sizeof(msg_ss_fast_t);
const uint8_t id = 0xa;

uint4.0_t state;
uint32_t time;

public:
uint4.0_t get_state() { return state; }
void set_state(uint4.0_t new_val) { state = new_val; }

uint32_t get_time() { return time; }
void set_time(uint32_t new_val) { time = new_val; }


void read(char* buf, size_t len){
  msg_ss_fast_t encoded;
  memcpy(&encoded,buf,len);
  //convert state
  //convert time
}


void write(Writeable& dest){
  msg_ss_fast_t encoded;
  //convert state
  //convert time
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static MSG_SS_FAST g_MSG_SS_FAST;
