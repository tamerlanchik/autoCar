#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include <TimerOne.h>
extern Logger Log;
Manager* manager;
int i=1;
double time=0;
Logger* Log;
void setup()
{
  Log = new Logger();
  Log->i("Setup");
  manager=new Manager();
  manager->init();
}

void loop()
{
  if(millis()-time > 1000){
    manager->sendTest();
    time=millis();
  }
  if(manager->radioAvailable()){
    manager->readRadio();
  }
}
