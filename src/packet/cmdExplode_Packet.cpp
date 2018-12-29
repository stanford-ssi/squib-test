#include "Packet.hpp"
#include <stdint.h>
#include <cstring>
typedef struct __attribute__((__packed__)) cmdexplode_packet_t {
} cmdexplode_packet_t;

class cmdExplode_Packet : public Packet{
protected:
const size_t length = 0;
const uint8_t id = 6;


public:

void read(char* buf, size_t len){
  cmdexplode_packet_t encoded;
  memcpy(&encoded,buf,len);}


void write(Writeable& dest){
  cmdexplode_packet_t encoded;
  dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len(){return length;}
};
