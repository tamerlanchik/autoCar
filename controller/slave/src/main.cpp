#include <Arduino.h>
#include <Manager.cpp>
#include <consts.h>

Manager manager;
void setup()
{
  manager.init();
}

void loop()
{
  if(manager.radioAvailable())
  {
    manager.writeRadio(manager.readRadio()*2);
  }
}
