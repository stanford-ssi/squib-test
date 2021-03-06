#pragma once
#include <cstdlib>

class Writeable {
public:
  virtual void write(char* msg, size_t len);
};

class Packet {
public:
  virtual void write(Writeable& dest);
  virtual void read(char* buf, size_t len);
  virtual size_t packet_len() = 0;
};

Writeable& operator<<(Writeable& w, Packet& p);

typedef enum {
  GPS_PKT = 0x02U,
  TELEM_PKT = 0x08U
} PacketID;
