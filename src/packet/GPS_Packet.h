#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) gps_packet_t {
  unsigned lat : 18;
  unsigned lon : 18;
  unsigned alt : 18;
  unsigned datetime : 32;
  unsigned lock : 1;
} gps_packet_t;

class GPS_Packet : public Packet{
protected:
const size_t length = sizeof(gps_packet_t);
const uint8_t id = 0xc;

double lat;
double lon;
double alt;
uint32_t datetime;
bool lock;

public:
double get_lat() { return lat; }
void set_lat(double new_val) { lat = new_val; }

double get_lon() { return lon; }
void set_lon(double new_val) { lon = new_val; }

double get_alt() { return alt; }
void set_alt(double new_val) { alt = new_val; }

uint32_t get_datetime() { return datetime; }
void set_datetime(uint32_t new_val) { datetime = new_val; }

bool get_lock() { return lock; }
void set_lock(bool new_val) { lock = new_val; }


void read(char* buf, size_t len){
  gps_packet_t encoded;
  memcpy(&encoded,buf,len);
  //convert lat
  //convert lon
  //convert alt
  //convert datetime
  //convert lock
}


void write(Writeable& dest){
  gps_packet_t encoded;
  //convert lat
  //convert lon
  //convert alt
  //convert datetime
  //convert lock
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len() { return length; }
};

static GPS_Packet g_GPS_Packet;
