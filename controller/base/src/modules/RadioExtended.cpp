//#include <nRF24L01.h>
#include "RadioExtended.h"
extern Logger Log;
RadioExtended::RadioExtended(char  a, char b):RF24(a, b){}
void RadioExtended::initRadio(const uint8_t*  adr1, const uint8_t* adr2, rf24_datarate_e r){
    this->begin();
    this->setDataRate(r);
    this->openReadingPipe(1,*adr1);
    this->openWritingPipe(*adr2);
    this->startListening();
}
bool RadioExtended::write(const char data[], int size)
{
    int i=0;
    bool fl=0;
    Log.d("Start sending");
    do{
       this->stopListening();
       fl=RF24::write(&data, size);
       this->startListening();
       if(!fl){
        delay(1*random(1, 5));
        Log.e("Cant send. Retry..");
      }
    }while((i++<10) && !fl);
    Log.e("Cant send at all");
    return fl;
}
