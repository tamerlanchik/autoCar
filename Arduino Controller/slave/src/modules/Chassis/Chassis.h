#if !defined HEADERCHASSIS
#define HEADERCHASSIS
#include <Arduino.h>
#include <pins.h>
#include "Logger.h"
#include "DigitalOutShield.h"
#define MIN(a,b) ((a)<(b)) ? (a) : (b)
struct MOVING_MODES{
  bool Stop[4];
  bool Forward[4];
  bool Backward[4];
  bool Right[4];
  bool Left[4];
};

class Chassis
{
private:
  int motorVal[motorChannelsCount];
  DigitalOutShield* dos;
  bool t;
  MOVING_MODES Modes = {
    {0,0,0,0},
    {0,1,0,1},
    {1,0,1,0},
    {1,0,0,1},
    {0,1,1,0}
  };
  void writeMotors(bool[]);
public:
  Chassis();
  void init();
  void setDOS(DigitalOutShield*);
  void setValue(int,int);
  void setValue(int[]);
  void setValue(float[]);
  void setValue(ChassisData*);
  int convertSpeed(float);
  void getValue(int[]);
  void test();
  static int F1(int);
};

#endif
