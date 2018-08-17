#if !defined HEADERENCODER
#define HEADERENCODER
#include <Arduino.h>
#include "Logger.h"
#include <pins.h>
class Encoder{
private:
  volatile unsigned long lastTimeMeasured[2], measureTime;
  bool moved[2];
public:
    float* mSpeed;
    volatile unsigned long precountAlert[2], counterAlert[2];
  Encoder(float[]);
  void handleEvent(unsigned char);
  void calcSpeed();
  unsigned long test();
};
#endif
