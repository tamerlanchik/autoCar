#include "Chassis.h"
extern Logger* Log;

Chassis::Chassis(){
  dos = NULL;
  motorVal[0]=motorVal[1]=0;
  Log->d("Create-1 Chassis");
  t=0;
}

void Chassis::init(){
  Log->d("Init Chassis");
}

void Chassis::setDOS(DigitalOutShield* d){
  dos = d;
}
void Chassis::setValue(int val[]){
  this->setValue(val[0],val[1]);
}
void Chassis::setValue(float val[]){
  int data[2];
  data[0] = convertSpeed(val[0]);
  data[1] = convertSpeed(val[1]);
  setValue(data);
}

void Chassis::setValue(ChassisData* data){
  setValue(data->getValue(0), data->getValue(1));
  /*for(unsigned int i = 0; i < motorChannelsCount; i++){
    motorVals[i] = data->getValue(i);
  }*/
}

int Chassis::convertSpeed(float a){
  return 50;
}
void Chassis::setValue(int a, int b){
  a = constrain(a, -255, 255);
  b = constrain(b, -255, 255);

  int epsRotate = 30;
  int epsMove = 30;
  //Log->d("setValue - MOTORS");

  int speedA = abs(a);
  int speedB = abs(b);
  if(abs(a) < epsMove){
    analogWrite(motors[4], speedB);
    analogWrite(motors[5], speedB);
    if(abs(b) < epsRotate){
      writeMotors(Modes.Stop);
    }else{
      if(b > 0){
        writeMotors(Modes.Right);
      }else{
        writeMotors(Modes.Left);
      }
    }
  }else{
    analogWrite(motors[4], speedA);
    analogWrite(motors[5], speedA);
    if(a > 0){
      writeMotors(Modes.Forward);
    }else{
      writeMotors(Modes.Backward);
    }
  }

  int speed = abs(a);
  speed = F1(speed);
  speed = map(speed, 0, 521, 0, 255);
}

void Chassis::getValue(int val[]){
  val[0]=motorVal[0];
  val[1]=motorVal[1];
}

int Chassis::F1(int x){
  if(x<100)
    return x;
  else if(x<=230)
    return (int)0.1*x+100;
  else
    return x;
}

void Chassis::test(){
  if(t){
    dos->write(B10101010);
    delay(100);
  }else{
    dos->write(B01010101);
    delay(100);
  }
  t = !t;
}

//private
void Chassis::writeMotors(bool values[]){
  if(areMotorsConnectedThroughtDOS){
    for(unsigned char i = 0; i<4; i++){
      dos->add(motors[i], values[i]);
    }
    dos->send();
  }else{
    for(unsigned char i = 0; i<4; i++){
      digitalWrite(motors[i], values[i]);
    }
  }
}
