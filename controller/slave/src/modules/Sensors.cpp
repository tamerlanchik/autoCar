#include "Sensors.h"
extern Logger* Log;
Sensors::Sensors():sonar1Servo()
{
  sonar1Servo.attach(sonarServoPin[0]);
  pinMode(sonar_trigPin[0], OUTPUT);
  pinMode(sonar_echoPin[0], INPUT);
  Log->d("Init Sensors");
}

void Sensors::getBorders(bool state[])
{
  Log->d("getBorders()");
  for(int i=0;i<4;i++)
  {
    state[i]=digitalRead(bordersSensor[i]);
  }
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
