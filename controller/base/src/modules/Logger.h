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
  Logger();
  void write(void*,char='d', char level='i')const;
  void d(void*,char='d')const;
  void e(void*,char='d')const;
  void i(void*,char='d')const;
};

#endif
