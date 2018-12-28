#include "Packet.hpp"
#include <stdint.h>

typedef struct __attribute__((__packed__)) gps_pkt_t
{
    unsigned lon : 12;
    unsigned lat : 12;
} gps_pkt_t;

class GPSPacket : public Packet
{
  protected:
    
    const uint8_t length = 10;
    const uint8_t id = 0x0b;

    double lat;
    double lon;

  public:

    double get_lat(){return lat;}
    void set_lat(double new_lat){lat = new_lat;}

    double get_lon(){return lon;}
    void set_lon(double new_lon){lon = new_lon;}

    void read(char* buf, size_t len)
    {
        gps_pkt_t encoded;
        memcpy(&encoded,buf,len);
        //lon = convert(encoded.lon)
        //lat = convert(encoded.lat)
        //todo: scripting
    }

    void write(Writeable& dest)
    {
        gps_pkt_t encoded;
        //encoded.lon = convert(lon);
        //encoded.lat = convert(lat);
        //todo: scripting
        dest.write((char *) &encoded, sizeof(encoded));
    }

    int packet_len(){return length;}
};

/*Writeable *operator<<(Writeable *w, GPSPacket p)
{
    p.write(w);
    return w;
}*/