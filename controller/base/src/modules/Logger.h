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
  void write(void*,char='s', char level='i')const;
  void d(void*,char='s')const;
  void e(void*,char='s')const;
  void i(void*,char='s')const;
};

#endif
