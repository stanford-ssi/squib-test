#include "Packet.hpp"
#include <stdint.h>
#include "string.h"
#include "packet/GPS_Packet.cpp"

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
        return new GPS_Packet;
        //todo: Scripting!
    }
}