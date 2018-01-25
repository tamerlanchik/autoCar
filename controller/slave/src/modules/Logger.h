#if !defined(HEADERLOG)
#define HEADERLOG
#include <Arduino.h>
#include "pins.h"
/*
Log modes (Android Log):
d: DEBUG
e: ERROR
i: INFO


*/
class Logger
{
public:
  Logger(int);
  void initSerial(int);
  void write(const char[],char)const;
  void d(const char[])const;
  void e(const char[])const;
  void i(const char[])const;
};

#endif
