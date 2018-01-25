#if !defined(HEADERLOG)
#define HEADERLOG
#include <Arduino.h>
/*
Log modes (Android Log):
d: DEBUG
e: ERROR
i: INFO


*/
static const int serialRate = 9600;
class Log
{
public:
  Log();
  void write(char[],char);
  void d(char[]);
  void e(char[]);
  void i(char[]);
};
#endif
