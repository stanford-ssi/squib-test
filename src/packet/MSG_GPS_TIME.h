#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) msg_gps_time_t {
  unsigned utctime : 32;
} msg_gps_time_t;
static_assert(sizeof(msg_gps_time_t) == 4, "msg_gps_time_t: unexpected packed length");

class MSG_GPS_TIME : public Packet{
protected:
const size_t length = sizeof(msg_gps_time_t);
const uint8_t id = 0x1;

uint32_t utctime;

public:
uint32_t get_utctime() { return utctime; }
void set_utctime(uint32_t new_val) { utctime = new_val; }


void read(char* buf, size_t len){
  msg_gps_time_t encoded;
  memcpy(&encoded,buf,len);
  //convert utctime
}


void write(Writeable& dest){
  msg_gps_time_t encoded;
  //convert utctime
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static MSG_GPS_TIME g_MSG_GPS_TIME;
