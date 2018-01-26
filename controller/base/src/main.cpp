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
  Log->d("BASE");
  manager=new Manager();
  manager->printLCD("Setup");
}

void loop()
{
  if((millis()-time) > 300){
    Log->d("sendTest time");
    manager->sendTest();
    time=millis();
  }
  if(manager->radioAvailable()){
    Log->d("Radio available");
    manager->readRadio();
    Log->d("readed radio");
  }
}
