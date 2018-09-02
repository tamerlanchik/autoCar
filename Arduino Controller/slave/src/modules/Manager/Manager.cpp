//slave
#include "Manager.h"
extern Logger* Log;

Manager::Manager(){
  chassis = new Chassis();
  chassis->init();
  Log->d("Manager inited");
}
void Manager::testing(){
  chassis->setValue(200, 0);
  delay(1000);
  chassis->setValue(0, 0);
  delay(500);
  chassis->setValue(-200, 0);
  delay(1000);
  chassis->setValue(0, 0);
  delay(500);
}
