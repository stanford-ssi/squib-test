#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) cmd_arm_t {
} cmd_arm_t;

class CMD_ARM : public Packet{
protected:
const size_t length = sizeof(cmd_arm_t);
const uint8_t id = 0x3;


public:

void read(char* buf, size_t len){
  cmd_arm_t encoded;
  memcpy(&encoded,buf,len);
}


void write(Writeable& dest){
  cmd_arm_t encoded;
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static CMD_ARM g_CMD_ARM;
