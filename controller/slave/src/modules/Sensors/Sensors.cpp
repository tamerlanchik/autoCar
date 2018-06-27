#include "Sensors.h"
extern Logger* Log;

Sensors::Sensors():sonar1Servo(){
  for(char i = 0; i < sonarCount; i++){
    lastSonarAck[i] = 0;
  }
  currAngle=0;
  Log->d("Create Sensors");
}

void Sensors::init(){
  sonar1Servo.attach(sonarServoPin[0]);
  pinMode(sonar_echoPin[0], INPUT);
  Log->d("Init Sensors");
}

int Sensors::getBorders(){
  Log->d("getBorders()->int");
  char data=0;
  for(int i=0;i<4;i++)
  {
    data*=2;
    data+=static_cast<int>(analogRead(bordersSensor[i]))/100;
  }
  return static_cast<int>(data);
}

void Sensors::getBorders(bool data[]){
  Log->d("getBorders(bool)");
  for(int i=0;i<4;i++)
  {
    data[i] = analogRead(bordersSensor[i])<300 ? true : false;
    int a = analogRead(bordersSensor[i]);
    Log->d(&a, 'd');
  }
}

SensorsPack Sensors::getValues() {
  SensorsPack data;
  getBorders(data.borders);
  return data;
}

int Sensors::getSonar(int numb,float angle,char mode){
  Log->d("getSonar()");
  int distance = -1;
  //numb = numb<0 ? 0 : numb; //проверка на отрицательный индекс
  //angle = angle>servoRange[numb][1] ? servoRange[numb][1] : angle;  //ограничение угла поворота
  //angle = angle<servoRange[numb][0] ? servoRange[numb][0] : angle;

  switch(mode){
    case ROTATE:
      rotate(numb, angle);
      break;
    case MEASURE:
      distance = readSonar(numb);
      break;
    case ROTATE_MEASURE:
      rotate(numb, angle, true);
      distance = readSonar(numb);
      break;
    default:
      Log->e("Unknown mode 'getSonar'");
      break;
  }
  return distance;
}

void Sensors::getValue(int data[]){
  switch(data[0])
  {
    case DISTANCE1:
      data[1]=getSonar(data[0],data[1],data[2]);
      break;
    case BORDERS:
      data[1]=getBorders();
      break;
    default:
      Log->d("Unknown sensor code");
      break;
  }
}

void Sensors::setDOS(DigitalOutShield* d){
  dos = d;
}

void Sensors::rotate(int numb, int angle, bool isWaitable){
  if(numb == DISTANCE1) sonar1Servo.write(angle);
  if(isWaitable){
    delay(2*abs(angle-currAngle));
  }
  currAngle = angle;
}

//private:
int Sensors::readSonar(int numb, int maxDist){
  maxDist = 200;
  Log->d("readSonar()");
  delay(MAX((int)(sonarTimeout - (millis() - lastSonarAck[numb])), 0));
  //int ppp = MAX(-10, 0);
  //delay(50);
  //if(millis() - lastSonarAck[numb] > sonarTimeout){
    dos->write(sonar_trigPin[numb], 0);
    delayMicroseconds(2);
    dos->write(sonar_trigPin[numb], 1);
    delayMicroseconds(10);
    dos->write(sonar_trigPin[numb], 0);
    int a = pulseIn(sonar_echoPin[numb], HIGH, maxDist*60)/58;  //максимальное расстояние ~206см
    lastSonarAck[numb] = millis();
    return a;
  /*}else{
    return -1;
  }*/
}
