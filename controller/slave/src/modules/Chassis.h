#if !defined HEADERCHASSIS
#define HEADERCHASSIS
#include <Arduino.h>
#include "pins.h"
#include "Logger.h"
class Chassis
{
private:
  int motorVal[2];
public:
  Chassis();
  void setValue(int,int);
  void getValue(int[]);
  static int F1(int);
};
#endif
