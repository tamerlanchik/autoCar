#include "Sensors.h"
extern Logger* Log;

Sensors::Sensors():sonar1Servo(),dos(NULL),encoderLastTimeChecked(0){
  for(unsigned int i = 0; i < sonarCount; i++){
    lastSonarAck[i] = 0;
  }
  currAngle=0;
  Log->d("Create Sensors");
}

void Sensors::init(){
  sonar1Servo.attach(sonarServoPin[0]);
  pinMode(sonar_echoPin[0], INPUT);
  pinMode(sonar_trigPin[0], OUTPUT);
  Log->d("Init Sensors");
}

void Sensors::update(){
  enc->calcSpeed();
}
void Sensors::shedulled(){
  enc->calcSpeed();
}

int Sensors::getBorders(bool t){
  Log->d("getBorders()->int");
  char data=0;
  for(int i=0;i<4;i++)
  {
    data*=2;
    data+=static_cast<int>(analogRead(borderSensorPins[i]))/100;
  }
  return static_cast<int>(data);
}

void Sensors::getBorders(bool data[], unsigned int count){
  Log->d("getBorders(bool)");
  int a;
  for(unsigned int i=0;i<count;i++)
  {
    a = analogRead(borderSensorPins[i]);
    data[i] = a<300 ? true : false;
    Log->d(&a, 'd');
  }
}

bool* Sensors::getBorders(){
  //Log->d("bool* getBorders()");
  this->updateBorderValues();
  return borderValues;
}

void Sensors::updateBorderValues(){
  //Log->d("updateBorderValues");
  int a;
  for(unsigned int i=0; i<borderSensorsCount; i++)
  {
    a = analogRead(borderSensorPins[i]);
    borderValues[i] = a<500 ? true : false;
    //Log->d(&a, 'd');
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
      data[1]=getBorders(0);
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

void Sensors::updateSpeed(unsigned long alertCount[]){
  for(unsigned int i = 0; i<2; i++){
    //precountAlert[i] = counterAlert[i];
    //counterAlert[i] = alertCount[i];
  }
}

//private:
int Sensors::readSonar(int numb, int maxDist){
  Log->d("readSonar()");
  if(numb<0 || numb > sonarCount-1){
    Log->e("Wrong 'numb' value");
  }

  delay(MAX((int)(sonarTimeout - (millis() - lastSonarAck[numb])), 0));

  if(isSonarConnectedThroughtDOS){
    dos->write(sonar_trigPin[numb], 0);
    delayMicroseconds(2);
    dos->write(sonar_trigPin[numb], 1);
    delayMicroseconds(10);
    dos->write(sonar_trigPin[numb], 0);
  }else{
    digitalWrite(sonar_trigPin[numb], 0);
    delayMicroseconds(2);
    digitalWrite(sonar_trigPin[numb], 1);
    delayMicroseconds(10);
    digitalWrite(sonar_trigPin[numb], 0);
  }
  unsigned int distance =  pulseIn(sonar_echoPin[numb], HIGH, sonarMaxDist*60)/58;  //максимальное расстояние ~206см
  lastSonarAck[numb] = millis();
}

void Sensors::setEncoder(Encoder* encoder){
  enc = encoder;
}

Encoder* Sensors::getEncoder(){
  return enc;
}
