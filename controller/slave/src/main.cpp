//slave
#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include "modules/Logger.h"
Logger* Log;
Manager* manager;
Message_template messag;
double k,t=0;
void setup()
{
  Log = new Logger();
  Log->d("CAR");
  manager = new Manager();
}

void loop()
{
  if(millis()-t>5){
    manager->readRadio();
    t=millis();
  }
  if(millis()-k>2000)
  {
    Log->i("Hi");
    k=millis();
  }
}
