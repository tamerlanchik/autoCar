#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include <TimerOne.h>
extern Logger Log;
Manager manager;
int i=1;

void setup()
{
  manager.init();
}

void loop()
{
  if(manager.radioAvailable()){
    manager.readRadio();
  }
}
