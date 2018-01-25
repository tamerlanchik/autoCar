#include <Arduino.h>
#include "modules/Manager.h"
#include "modules/pins.h"
#include <TimerOne.h>
extern Logger Log;
Manager manager;
int i=1;
void sendTest(){
  manager.sendTest();
}
void setup()
{
  manager.init();
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(sendTest);
}

void loop()
{
  if(manager.radioAvailable()){
    noInterrupts();
    manager.readRadio();
    interrupts();
  }
}
