//#include <nRF24L01.h>
#include "RadioExtended.h"
RadioExtended::RadioExtended(char  a, char b):RF24(a, b){}
void RadioExtended::initRadio(int*  adr1, int* adr2, rf24_datarate_e r){
    this->begin();
    this->setDataRate(r);
    this->openReadingPipe(1,*adr1);
    this->openWritingPipe(*adr2);
    this->startListening();
}
bool RadioExtended::write(char data[], int size)
{
    int i=0;
    bool fl=0;
    do{
       this->stopListening();
       fl=RF24::write(&data, size);
       this->startListening();
       if(!fl)
        delay(1*random(1, 5));
    }while((i++<10) && !fl);
    return fl;
}
