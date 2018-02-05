//base
#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include <TimerOne.h>
int i=1;
double time=0;
int time2=0;
volatile bool temp;
Logger* Log;
Manager* manager;
void setup()
{
  Log = new Logger();
  Log->d("BASE");
  manager=new Manager();
}

void loop()
{
  while(!manager->makeRadioConnection())
  {
    manager->printLCD("No conn");
  }
  /*if((millis()-time) > 500){
    Log->d("sendTest time");
    manager->sendTest();
    time=millis();
  }
  if(manager->radioAvailable()){
    Log->d("Radio available");
    manager->readRadio();
    Log->d("readed radio");
  }*/
  manager->ascControl();
  //manager->ascSensors(0);
  manager->readRadio();
  delay(100);
  //manager->makeRadioConnection();
  //delay(1000);
}
