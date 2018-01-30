//slave
#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include "modules/Logger.h"
Logger* Log;
Manager* manager;
Message_template messag;
void setup()
{
  Log = new Logger();
  Log->d("CAR");
  manager = new Manager();
}

void loop()
{
  /*if(manager->radioAvailable())
  {
    Log->d("Radio available");
    messag=manager->readRadio();
    messag.data[0]*=1000;
    manager->writeRadio(messag);
  }*/
  manager->readRadio();
}
