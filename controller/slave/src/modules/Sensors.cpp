#include "Sensors.h"
extern Logger* Log;
Sensors::Sensors():sonar1Servo()
{
  sonar1Servo.attach(sonarServoPin[0]);
  pinMode(sonar_trigPin[0], OUTPUT);
  pinMode(sonar_echoPin[0], INPUT);
  Log->d("Init Sensors");
}

int Sensors::getBorders()
{
  Log->d("getBorders()");
  char data=0;
  for(int i=0;i<4;i++)
  {
    data*=2+digitalRead(bordersSensor[i]);
  }
  return static_cast<int>(data);
}

int Sensors::getSonar(int angle,int numb)
{
  if(numb==1)
  {
    sonar1Servo.write(angle);
    return readSonar(numb);
  }
  return 1;
}
void Sensors::getValue(int data[])
{
  switch(data[0])
  {
    case SONAR_ID:
      data[1]=getSonar(data[1],data[2]);
      break;
    case BORDERS_ID:
      data[1]=getBorders();
      break;
    default:
      Log->d("Unknown sensor code");
      break;
  }
}
//private:
int Sensors::readSonar(int numb){
  Log->d("readSonar()");
  digitalWrite(sonar_trigPin[numb-1], LOW);
  delayMicroseconds(2);
  digitalWrite(sonar_trigPin[numb-1], HIGH);
  delayMicroseconds(10);
  digitalWrite(sonar_trigPin[numb-1], LOW);
  return pulseIn(sonar_echoPin[numb-1], HIGH)/58;
}
