//#include <nRF24L01.h>
#include "RadioExtended.h"
extern Logger* Log;
RadioExtended::RadioExtended(int  a, int b, const uint8_t*  adr1,
                            const uint8_t* adr2, rf24_datarate_e r,
                            rf24_pa_dbm_e l, bool role):RF24(a, b)
{
  this->begin();
  this->setDataRate(r);
  this->setPALevel(RF24_PA_LOW);
  this->setRetries(15, 5);
  //this->setAutoAck(1);                    // Ensure autoACK is enabled
  //this->enableAckPayload();
  //role: 1-base, 0-slave
  if(role){
    this->openReadingPipe(1,*adr2);
    this->openWritingPipe(*adr1);
  }
  else{
    this->openReadingPipe(1,*adr1);
    this->openWritingPipe(*adr2);
  }
  this->startListening();
  delay(300);
  Log->d("Radio inited");
}
bool RadioExtended::write(void* data, int size)
{
    int i=0;
    bool fl=1;
    Log->d("Start sending");
    do{
       this->stopListening();
       Log->d("Stop litening");
       fl=RF24::write(data, size);
       Log->e("Try to wrote");
       this->startListening();
       if(!fl){
        delay(1*random(1, 5));
        Log->e("Cant send. Retry..");
      }
      else{
        Log->d("Success send");
      }
    }while((i++<10) && !fl);
    Log->e("Send tries end");
    return fl;
    //this->stopListening();
    //RF24::write(data, size);
    //this->startListening();
    //return 1;
}
