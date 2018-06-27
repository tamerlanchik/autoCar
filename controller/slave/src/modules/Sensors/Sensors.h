#if !defined HEADERSENSORS
#define HEADERSENSORS
#include <Arduino.h>
#include "Logger.h"
#include <Servo.h>
#include <pins.h>
#include "DigitalOutShield.h"

class Sensors
{
private:
  Servo sonar1Servo;
  Servo sonar2Servo;
  DigitalOutShield* dos;
  int currAngle;
  int readSonar(int, int=200);  //maxDist = 2.0m
  unsigned long long lastSonarAck[sonarCount];
public:
  enum SonarMode {ROTATE_MEASURE, MEASURE, ROTATE};
  enum SensorAck {BORDERS, DISTANCE1};
  Sensors();
  void init();
  void setDOS(DigitalOutShield*);
  int getBorders();
  void getBorders(bool[]);
  int getSonar(int,float,char);
  void getValue(int[]);
  SensorsPack getValues();
  void rotate(int,int,bool=false);
};
#endif
