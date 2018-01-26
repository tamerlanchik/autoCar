//slave
#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include "modules/Logger.h"
//int speed = 115200;
Logger* Log;
Manager* manager;
void setup()
{
  Log = new Logger();
  //Serial.begin(115200);
  //delay(400);
  Log->d("Setup");
  manager = new Manager();
  //manager->init();
}

void loop()
{
  if(manager->radioAvailable())
  {
    Log->d("Radio available");
    manager->writeRadio(manager->readRadio()*2);
  }
}
