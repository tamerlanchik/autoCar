#include "Radio1Extended.h"
extern Logger* Log;
Radio1Extended::Radio1Extended(int CE, int CSN, bool role, int size){
  Mirf.csnPin = CSN;
  Mirf.cePin = CE;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = size;
  if(role){ //master
    Mirf.setRADDR((byte *)"clie1");
    Mirf.setTADDR((byte *)"serv1");
  }else{
    Mirf.setRADDR((byte *)"serv1");
    Mirf.setTADDR((byte *)"clie1");
  }
  Mirf.config();
  Log->d("Mirf inited");
}

void Radio1Extended::write(void* data){
  Log->d("Mirf writing");
  Mirf.send((byte *) data);
}
