#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) cmd_gps_t {
  unsigned power : 1;
} cmd_gps_t;

class CMD_GPS : public Packet{
protected:
const size_t length = sizeof(cmd_gps_t);
const uint8_t id = 0x4;

bool power;

public:
bool get_power() { return power; }
void set_power(bool new_val) { power = new_val; }


void read(char* buf, size_t len){
  cmd_gps_t encoded;
  memcpy(&encoded,buf,len);
  //convert power
}


void write(Writeable& dest){
  cmd_gps_t encoded;
  //convert power
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static CMD_GPS g_CMD_GPS;
