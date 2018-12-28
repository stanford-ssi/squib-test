#include "Packet.hpp"
#include <stdint.h>
#include "GPSPacket.cpp"
#include "string.h"

Writeable &operator<<(Writeable &w, Packet *p)
{
    p->write(w);
    return w;
}

Packet *new_packet(PacketID id)
{
    switch (id)
    {
    case 0x0B:
        return new GPSPacket;
        //todo: Scripting!
    }
}