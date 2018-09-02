//#include <nRF24L01.h>
#include "RadioExtended.h"
extern Logger* Log;
RadioExtended::RadioExtended(int  a, int b, const uint8_t*  adr1,
                            const uint8_t* adr2, rf24_datarate_e r,
                            rf24_pa_dbm_e l, bool role):RF24(a, b),
                            connectionTimeout(2),checkConnectionTimeout(300),lastConnectionTime(0)
{
  this->begin();
  this->setDataRate(r);
  this->setPALevel(l);
  this->setRetries(3, 3);
  //this->setCRCLength(8);
  //this->setAutoAck(1);                    // Ensure autoACK is enabled
  //this->enableAckPayload();
  //this->enableDynamicPayloads();
  //role: 1-base, 0-slave
  if(role){
    this->openReadingPipe(1,*adr2);
    this->openWritingPipe(*adr1);
  }
  else{
    this->openReadingPipe(1,*adr1);
    this->openWritingPipe(*adr2);
  }
  //this->powerUp();
  //this->setPayloadSize(32);
  this->startListening();
  Log->d("Radio inited");
}
bool RadioExtended::write(void* data, int size)
{
  while(millis()-lastConnectionTime <= connectionTimeout) {}

  this->stopListening();
  bool fl = RF24::write(data,size);
  this->startListening();

  lastConnectionTime = millis();

  return fl;
}
bool RadioExtended::writeChecked(void* data, int size)
{
    int i=0;
    bool fl;
    do{
       this->stopListening();
       fl=write(data, size);
       this->startListening();
       if(!fl) delay(1*random(1, 5));
    }while((i++<10) && !fl);
    if(!fl){
      Log->e("Radio: Cant send");
    }
    else{
      Log->d("Success send");
    }
    return fl;
}

bool RadioExtended::isTimeToCheckConnection()
 {
   if(millis()-lastCheckConnectionTime > checkConnectionTimeout)
   {
     return true;
   }
   else {return false;}
}

bool RadioExtended::debugAckPayloads(void* data,int len,void* answer)
{
  //if cannot send message
  Log->d("debugPayLoads");
  if(!this->write(data,len))
  {
    Log->e("Cant send ack");
    return false;
  }
  else Log->d("Ack is sent");

    //waiting for an answer
  int tmt=millis()/10;
  while((millis()/10-tmt)<=2)
  {
    if(this->available())
    {
      this->read(answer,len);
      if(static_cast<Message_template*>(answer)->mode == static_cast<Message_template*>(data)->mode)
      {
        Log->d("Correct ans got");
        return true;
      }
      else
      {
        Log->e("Prev or wrong ans got");
        continue;
      }
    }
    //else {delay(1);}
  }
  Log->e("No ans");
  return 0;
}
bool RadioExtended::ackRequest(void* data,int len,void* answer)
{

  //if cannot send message
  Log->d("ackRequest");
  if(!this->write(data,len))
  {
    Log->e("Cant send ack");
    return false;
  }
  else Log->d("Ack is sent");

    //waiting for an answer
  double tmt=millis()/10;
  while((millis()/10.0-tmt)<=1)
  {
    if(this->available())
    {
      this->read(answer,len);
      if(static_cast<Message_template*>(answer)->mode == static_cast<Message_template*>(data)->mode)
      {
        Log->d("Correct ans got");
        return true;
      }
      else
      {
        Log->e("Prev or wrong ans got");
        continue;
      }
    }
    else {delay(1);}
  }
  Log->e("No ans");
  return 0;
}
