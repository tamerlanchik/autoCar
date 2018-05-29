//slave
#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include "modules/Logger.h"
Logger* Log;
Manager* manager;


Message_template messag;
double k,t=0;
int i=0;
void setup()
{
  Log = new Logger();

  Log->d("CAR");
  manager = new Manager();
}

void loop()
{
  manager->readRadio();
  manager->guard();
}
