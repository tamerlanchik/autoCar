#if !defined(HEADERLOG)
#define HEADERLOG
#include "pins.h"
//#include <Arduino.h>
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
  void write(char[],char);
  void d(char[]);
  void e(char[]);
  void i(char[]);
};
#endif
