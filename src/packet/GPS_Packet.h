#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) gps_packet_t {
  unsigned lat : 18;
  unsigned lon : 18;
  unsigned lock : 1;
} gps_packet_t;

class GPS_Packet : public Packet{
protected:
const size_t length = 5;
const uint8_t id = 12;

double lat;
double lon;
bool lock;

public:
double get_lat(){return lat;}
void set_lat(double new_val){lat = new_val;}

double get_lon(){return lon;}
void set_lon(double new_val){lon = new_val;}

bool get_lock(){return lock;}
void set_lock(bool new_val){lock = new_val;}


void read(char* buf, size_t len){
  gps_packet_t encoded;
  memcpy(&encoded,buf,len);
  //convert lat
  //convert lon
  //convert lock
}


void write(Writeable& dest){
  gps_packet_t encoded;
  //convert lat
  //convert lon
  //convert lock
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len(){return length;}
};
