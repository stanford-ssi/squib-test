#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) cmd_disarm_t {
} cmd_disarm_t;
static_assert(sizeof(cmd_disarm_t) == 0, "cmd_disarm_t: unexpected packed length");

class CMD_DISARM : public Packet{
protected:
const size_t length = sizeof(cmd_disarm_t);
const uint8_t id = 0x4;


public:

void read(char* buf, size_t len){
  cmd_disarm_t encoded;
  memcpy(&encoded,buf,len);
}


void write(Writeable& dest){
  cmd_disarm_t encoded;
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static CMD_DISARM g_CMD_DISARM;
