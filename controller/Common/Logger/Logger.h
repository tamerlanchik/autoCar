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
  void write(const void*,char='s', char ='i');
  void d(void*,char='s');
  void e(void*,char='s');
  void i(void*,char='s');
};

#endif
