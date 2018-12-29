#include <stdint.h>
#include "Packet.h"
#include "packet/GPS_Packet.h"


//new data comes in!
class Train : public Writeable{
    void write(char* msg, size_t len){

    }
};

int main(){
    char data[] = {1,2,3,4};

    Writeable * dest = new Train();
    Writeable & ref = *dest;

    PacketID id;
    Packet * new_pkt = new_packet(id);
    new_pkt->read(data,sizeof(data));

    switch (id) {
        case GPS_PKT:
            //do something
            break;
        case TELEM_PKT:
            //something else
            break;
    }

    ref << new_pkt; 

    free(new_pkt);
}
