#if !defined HEADERSENSORS
#define HEADERSENSORS
#include <Arduino.h>
#include "Logger.h"
#include <Servo.h>
#include <pins.h>
#include "DigitalOutShield.h"
#include <Encoder.h>

class Sensors
{
private:
  Servo sonar1Servo;
  Servo sonar2Servo;
  DigitalOutShield* dos;
  int currAngle;
  int readSonar(int, int=200);  //maxDist = 2.0m
  unsigned long long lastSonarAck[sonarCount];
  unsigned long encoderLastTimeChecked;
public:
  Encoder* enc;
  bool borderValues[borderSensorsCount];
  static unsigned long precountAlert1[2], counterAlert1[2];
  enum SonarMode {ROTATE_MEASURE, MEASURE, ROTATE};
  enum SensorAck {DISTANCE1, BORDERS};
  Sensors();
  void init();
  void update();
  void shedulled();
  void setDOS(DigitalOutShield*);
  void setEncoder(Encoder*);
  Encoder* getEncoder();
  int getBorders(bool);
  void getBorders(bool[], unsigned int);
  bool* getBorders();
  void updateBorderValues();
  int getSonar(int numb,float angle,char mode);
  void getValue(int[]);
  SensorsPack getValues();
  void rotate(int,int,bool=false);
  void updateSpeed(unsigned long[]);
};
#endif
