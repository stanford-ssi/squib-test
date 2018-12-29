#include "Packet.hpp"
#include <stdint.h>
#include <cstring>

typedef struct __attribute__((__packed__)) telem10hz_packet_t {
unsigned state : 5;
} telem10hz_packet_t;

class Telem10Hz_Packet : public Packet{
protected:
const size_t length = 1;
const uint8_t id = 4;

uint8_t state;

public:
uint8_t get_state(){return state;}
void set_state(uint8_t new_val){state = new_val;}

void read(char* buf, size_t len){
telem10hz_packet_t encoded;
memcpy(&encoded,buf,len);

//convert state
}

void write(Writeable& dest){
telem10hz_packet_t encoded;

//convert state
dest.write((char *) &encoded, sizeof(encoded));
}

size_t packet_len(){return length;}
};
