#include "Sensors.h"
extern Logger* Log;
Sensors::Sensors():sonar1Servo()
{
  sonar1Servo.attach(sonarServoPin[0]);
  pinMode(sonar_trigPin[0], OUTPUT);
  pinMode(sonar_echoPin[0], INPUT);
  for(int i=0;i<4;i++)
  {
    pinMode(bordersSensor[i], INPUT);
  }
  Log->d("Init Sensors");
}

int Sensors::getBorders()
{
  Log->d("getBorders()");
  char data=0;
  for(int i=0;i<4;i++)
  {
    data*=2;
    data+=static_cast<int>(analogRead(bordersSensor[i]))/100;
    //data+=1;
  }
  return static_cast<int>(data);
}
void Sensors::getBorders(bool data[])
{
  Log->d("getBorders()");
  for(int i=0;i<4;i++)
  {
    //data[i]=static_cast<int>(analogRead(bordersSensor[i]))/100;
    data[i] = analogRead(bordersSensor[i])<300 ? true : false;
    int a = analogRead(bordersSensor[i]);
    Log->d(&a, 'd');
  }
}

int Sensors::getSonar(int numb,int angle,int mode)
{
  if(numb==89)
  {
    sonar1Servo.write(angle);
    if(mode)
      return readSonar(numb);
    else
      return 4;
  }
  return 3;
}
void Sensors::getValue(int data[])
{
  switch(data[0])
  {
    case 89:
      data[1]=getSonar(data[0],data[1],data[2]);
      break;
    case 90:
      data[1]=getSonar(data[0],data[1],data[2]);
      break;
    case 33:
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
SensorsPack Sensors::getValues() {
  SensorsPack data;
  getBorders(data.borders);
  //data.sonarValue = getSonar(89,90,1);
  return data;
}
