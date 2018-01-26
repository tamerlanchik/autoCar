//base
#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include <TimerOne.h>
int i=1;
double time=0;
Logger* Log;
Manager* manager;
void setup()
{
  Log = new Logger();
  Log->d("Setup");
  manager=new Manager();
  manager->printLCD("Setup");
}

void loop()
{
  if(millis()-time > 1000){
    Log->d("sendTest time");
    manager->sendTest();
    time=millis();
  }
  if(manager->radioAvailable()){
    manager->readRadio();
  }
}
