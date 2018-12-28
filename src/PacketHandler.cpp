#include <stdint.h>
#include "Packet.hpp"
#include "GPSPacket.cpp"


//new data comes in!
class Train : public Writeable{
    void write(char* msg, size_t len){

    }
};

void main(){

    char data[] = {1,2,3,4};

    Writeable * dest = new Train;

    PacketID id;

    Packet * new_pkt = new_packet(id);

    new_pkt->read(data,sizeof(data));

    switch (id)
    {
        case GPS_PKT:
            //do something
            break;
        case TELEM_PKT:
            //something else
            break;
    }

    dest << new_pkt; 

    free(new_pkt);

}