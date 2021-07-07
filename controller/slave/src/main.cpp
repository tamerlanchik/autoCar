//slave
#define DEBUG

#include <Arduino.h>
#include "Manager.h"
#include "pins.h"
#include "Logger.h"
#include <SPI.h>
Logger* Log;
Manager* manager;

void setup(){
  Log = new Logger();
  Log->d("CAR");
}

void loop()
{
  digitalWrite(9, 1);
  delay(1000);
  digitalWrite(9, 0);
  delay(500);
}
