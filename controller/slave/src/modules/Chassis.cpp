#include "Chassis.h"
extern Logger* Log;
Chassis::Chassis()
{
  motorVal[0]=motorVal[1]=0;
  Log->d("Init Chassis");
}
void Chassis::setValue(int a, int b)
{
}
void Chassis::getValue(int val[])
{
  val[0]=motorVal[0];
  val[1]=motorVal[1];
}
