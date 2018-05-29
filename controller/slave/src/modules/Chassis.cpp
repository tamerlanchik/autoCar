#include "Chassis.h"
extern Logger* Log;
Chassis::Chassis()
{
  motorVal[0]=motorVal[1]=0;
  Log->d("Init Chassis");
}
void Chassis::setValue(int a, int b)
{
  Log->d("setValue - MOTORS");
  if(b==0){
    if(a>10)
    {
        digitalWrite(motors[0],1);
        digitalWrite(motors[1],0);
        digitalWrite(motors[2],1);
        digitalWrite(motors[3],0);
    }
    else if(a<-10)
    {
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],1);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],1);
    }
    else if(a>=-10 && a<=10)
    {
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],0);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],0);
    }
  }
  else{
    if(b>10)
    {
        digitalWrite(motors[0],1);
        digitalWrite(motors[1],0);
        digitalWrite(motors[2],0);
        digitalWrite(motors[3],1);
    }
    else if(b<-10)
    {
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],1);
      digitalWrite(motors[2],1);
      digitalWrite(motors[3],0);
    }
    else if(b>=-10 && a<=10)
    {
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],0);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],0);
    }
  }
}
void Chassis::getValue(int val[])
{
  val[0]=motorVal[0];
  val[1]=motorVal[1];
}
