#include "Packet.h"
#include <stdint.h>
#include "string.h"
#include "packet/CMD_GPS.h"

Writeable& operator<<(Writeable &w, Packet& p) {
  p.write(w);
  return w;
}
