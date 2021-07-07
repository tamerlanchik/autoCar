//slave
#include "Manager.h"
extern Logger* Log;

Manager::Manager(){
  chassis = new Chassis();
  chassis->init();
  Log->d("Manager inited");
}
void Manager::testing(){
  long long t = millis();
  while(millis()-t < 4000){
    chassis->setValue(constrain(f(millis(), t), -255, 255), 0);
  }
}
int Manager::f(long long x, long long x0){
  x -= x0;
  if(x >= 0 && x < 980) return (x+40)/4;
  else if(x >= 980 && x < 1200) return 200;
  else if(x >= 1200 && x < 1800) return 0;
  else if(x>= 1800 && x < 2780) return -(x-1800+40)/4;
  else if(x >= 2780 && x< 3000) return -200;
  else return 0;
}
