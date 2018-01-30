#if !defined HEADERSENSORS
#define HEADERSENSORS
#include <Arduino.h>
#include "Logger.h"
class Sensors
{
private:
public:
  Sensors();
  void getBorders(bool[]);
  int getSonar(int);
};
#endif
