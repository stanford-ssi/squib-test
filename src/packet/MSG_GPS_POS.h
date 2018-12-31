#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) msg_gps_pos_t {
  unsigned lat : 18;
  unsigned lon : 18;
  unsigned alt : 18;
  unsigned hdop : 8;
} msg_gps_pos_t;

class MSG_GPS_POS : public Packet{
protected:
const size_t length = sizeof(msg_gps_pos_t);
const uint8_t id = 0x0;

double lat;
double lon;
double alt;
double hdop;

public:
double get_lat() { return lat; }
void set_lat(double new_val) { lat = new_val; }

double get_lon() { return lon; }
void set_lon(double new_val) { lon = new_val; }

double get_alt() { return alt; }
void set_alt(double new_val) { alt = new_val; }

double get_hdop() { return hdop; }
void set_hdop(double new_val) { hdop = new_val; }


void read(char* buf, size_t len){
  msg_gps_pos_t encoded;
  memcpy(&encoded,buf,len);
  //convert lat
  //convert lon
  //convert alt
  //convert hdop
}


void write(Writeable& dest){
  msg_gps_pos_t encoded;
  //convert lat
  //convert lon
  //convert alt
  //convert hdop
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static MSG_GPS_POS g_MSG_GPS_POS;
