#pragma once
#include <cstdlib>

class Writeable
{
    public:
        virtual void write(char* msg, size_t len);
};

class Packet
{
  public:
    virtual void encode(char *buf);
    virtual void decode(char *buf);
    virtual int packet_len() = 0;
    virtual void write(Writeable& dest);
    virtual void read(char* buf, size_t len);
};

Packet *new_packet(PacketID id);

typedef enum {
  GPS_PKT = 0x02U,
  TELEM_PKT = 0x08U
} PacketID;