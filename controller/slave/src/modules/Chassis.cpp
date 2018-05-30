#include "Chassis.h"
extern Logger* Log;
Chassis::Chassis()
{
  motorVal[0]=motorVal[1]=0;
  Log->d("Init Chassis");
  //analogWrite(motors[4], 200);
  //digitalWrite(motors[4], 1);
}
void Chassis::setValue(int a, int b)
{
  Log->d("setValue - MOTORS");
  //analogWrite(motors[5], map(-a, -512, 512, 0, 255));
  if(b<5 && b>-5){
    if(a>5)
    {
        digitalWrite(motors[0],1);
        digitalWrite(motors[1],0);
        digitalWrite(motors[2],1);
        digitalWrite(motors[3],0);
    }
    else if(a<-5)
    {
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],1);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],1);
    }
    else if(a>=-5 && a<=5)
    {
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],0);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],0);
    }
  }
  else{
    if(b>5)
    {
        digitalWrite(motors[0],1);
        digitalWrite(motors[1],0);
        digitalWrite(motors[2],0);
        digitalWrite(motors[3],1);
    }
    else if(b<-5)
    {
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],1);
      digitalWrite(motors[2],1);
      digitalWrite(motors[3],0);
    }
    else if(b>=-5 && a<=5)
    {
      digitalWrite(motors[0],0);
      digitalWrite(motors[1],0);
      digitalWrite(motors[2],0);
      digitalWrite(motors[3],0);
    }
  }
  //int speed = map(abs(a), 0, 521, 0, 255);
  int speed = abs(a);
  speed = F1(speed);
  speed = map(speed, 0, 521, 0, 255);
  /*if(abs(b)<50)
    b = 0;*/
  analogWrite(motors[5], speed);
}
void Chassis::getValue(int val[]){
  val[0]=motorVal[0];
  val[1]=motorVal[1];
}

int Chassis::F1(int x){
  if(x<100)
    return x;
  else if(x<=500)
    return 0.2*x+100;
  else
    return x;
}
