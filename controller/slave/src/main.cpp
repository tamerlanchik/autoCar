#include <Arduino.h>
#include <modules/Manager.h>
#include <modules/pins.h>
extern Logger Log;
Manager* manager;
void setup()
{
  Serial.begin(115200);
  delay(400);
  Log.i("Setup");
  manager = new Manager();
  manager->init();
}

void loop()
{
  if(manager->radioAvailable())
  {
    Log.i("Radio available");
    manager->writeRadio(manager->readRadio()*2);
  }
}
