#if !defined(HEADERREee)
#define HEADERREee
#include "Logger.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
class Radio1Extended : public Nrf24l
{
private:

public:
  Radio1Extended(int,int,bool,int);
  void write(void*);
};
#endif
