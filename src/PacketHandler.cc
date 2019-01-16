#include <stdint.h>
#include "Packet.h"
#include "packet/CMD_GPS.h"


//new data comes in!
class Train : public Writeable{
  void write(char* msg, size_t len) {}
};

/*
int main(){
  char data[] = {1,2,3,4};

  //Writeable * dest = new Train();
  //Writeable & ref = *dest;

  Train ref;

  g_CMD_GPS.read(data,sizeof(data));

  ref << g_CMD_GPS; 
}
*/
