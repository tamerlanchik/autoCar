#if !defined HEADERSENSORS
#define HEADERSENSORS
#include <Arduino.h>
#include "Logger.h"
#include <Servo.h>
#include "pins.h"
class Sensors
{
private:
  Servo sonar1Servo;
  int readSonar(int);
public:
  Sensors();
  void getBorders(bool[]);
  int getSonar(int,int);
};
#endif
