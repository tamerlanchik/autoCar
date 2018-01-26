//#include <nRF24L01.h>
#include "RadioExtended.h"
extern Logger* Log;
RadioExtended::RadioExtended(int  a, int b, const uint8_t*  adr1, const uint8_t* adr2, rf24_datarate_e r):RF24(a, b){
  this->begin();
  this->setDataRate(r);
  this->openReadingPipe(1,*adr2);
  this->openWritingPipe(*adr1);
  this->startListening();
  delay(300);
  Log->d("Radio inited");
}
bool RadioExtended::writee(const char data[], int size)
{
    int i=0;
    bool fl=0;
    Log->d("Start sending");
    do{
       this->stopListening();
       Log->d("Stop litening");
       fl=this->write(&data, size);
       Log->e("Try to wrote");
       this->startListening();
       if(!fl){
        delay(1*random(1, 5));
        Log->e("Cant send. Retry..");
      }
    }while((i++<10) && !fl);
    Log->e("Cant send at all");
    return fl;
}
