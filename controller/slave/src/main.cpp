//slave
#include <Arduino.h>
#include "Manager.h"
#include "pins.h"
#include "Logger.h"
#include "DigitalOutShield.h"
#include <SPI.h>
#include <Servo.h>
Logger* Log;
Manager* manager;
void setup()
{

  Log = new Logger();
  Log->d("CAR");
  manager = new Manager();
}

void loop()
{
  manager->readRadio();
  //manager->guard();
  //manager->testing();
}
