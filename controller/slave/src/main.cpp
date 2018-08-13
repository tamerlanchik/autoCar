//slave
#define DEBUG

#include <Arduino.h>
#include "Manager.h"
#include "pins.h"
#include "Logger.h"
#include "DigitalOutShield.h"
#include <SPI.h>
#include <Servo.h>
#include <Encoder.h>
void left();
void right();
void speedWatch();
Logger* Log;
Manager* manager;
Encoder* encoder;
Model* model;
//Servo s;
volatile unsigned long int counterAlert[2] = {0,0},
                           precountAlert[2] = {0,0};
float speed[2] = {0,0};


volatile unsigned long int L=0, R=0, preL=0, preR=0;
volatile bool ffL=0,ffR=0;
unsigned long int tL=0, tR=0, tT=0, measureTime = 0, ttt=0;
//R = 34mm
//L = 214mm
//N = 40;
void setup(){
  Log = new Logger();
  Log->d("CAR");
  model = new Model();
  encoder = new Encoder(model->linearSpeed);
  manager = new Manager();
  manager->getSensorMaster()->setEncoder(encoder);
  //manager->setModel(&model);
  attachInterrupt(0, left, HIGH);
  attachInterrupt(1, right, CHANGE);
  //s.attach(9);
  //delay(3000);
}

void loop()
{
  //manager->testing();
  manager->readRadio();
}
void left(){
  encoder->handleEvent(0);
}
void right(){
  encoder->handleEvent(1);
}
void speedWatch(){
  for(unsigned int i = 0; i<2; i++){
      speed[i] = dL * (counterAlert[i] - precountAlert[i]) / (millis() - measureTime);
      speed[i] /= 2;
      speed[i] *= 1000;
      precountAlert[i] = counterAlert[i];
  }
  measureTime = millis();
}
